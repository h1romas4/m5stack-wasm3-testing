#include "esp_system.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <M5Stack.h>

#include "wasm3.h"
#include "m3_env.h"

#include "extra/fib32.wasm.h"

#define FATAL(msg, ...) { M5.Lcd.printf("Fatal: " msg "\n", ##__VA_ARGS__); return; }

static void run_wasm(void)
{
    M3Result result = m3Err_none;

    uint8_t* wasm = (uint8_t*)fib32_wasm;
    uint32_t fsize = fib32_wasm_len-1;

    M5.Lcd.printf("Loading WebAssembly...\n");
    IM3Environment env = m3_NewEnvironment ();
    if (!env) FATAL("m3_NewEnvironment failed");
    M5.Lcd.printf(" @m3_NewEnvironment: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    IM3Runtime runtime = m3_NewRuntime (env, 1024, NULL);
    if (!runtime) FATAL("m3_NewRuntime failed");
    M5.Lcd.printf(" @m3_NewRuntime: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    IM3Module module;
    result = m3_ParseModule (env, &module, wasm, fsize);
    if (result) FATAL("m3_ParseModule: %s", result);
    M5.Lcd.printf(" @m3_ParseModule: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    result = m3_LoadModule (runtime, module);
    if (result) FATAL("m3_LoadModule: %s", result);
    M5.Lcd.printf(" @m3_LoadModule: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    IM3Function f;
    result = m3_FindFunction (&f, runtime, "fib");
    if (result) FATAL("m3_FindFunction: %s", result);
    M5.Lcd.printf(" @m3_FindFunction: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    M5.Lcd.printf("Running...\n");

    const char* i_argv[2] = { "18", NULL };
    M5.Lcd.printf(" *fib(%s)\n", i_argv[0]);
    result = m3_CallWithArgs (f, 1, i_argv);

    if (result) FATAL("m3_CallWithArgs: %s", result);
    M5.Lcd.printf(" @m3_CallWithArgs: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    long value = *(uint64_t*)(runtime->stack);
    M5.Lcd.printf("Result: %ld\n", value);
}

// the setup routine runs once when M5Stack starts up
void setup(){

    // Initialize the M5Stack object
    M5.begin();

    M5.Lcd.printf("\nWasm3 v" M3_VERSION " on ESP32, build " __DATE__ " " __TIME__ "\n\n");
    M5.Lcd.printf("free memory: %d byte\n\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    // Run wasm3
    clock_t start = clock();
    run_wasm();
    clock_t end = clock();

    M5.Lcd.printf("Elapsed: %ld ms\n\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    M5.Lcd.printf("free memory: %d byte\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
}

// the loop routine runs over and over again forever
void loop() {

}
