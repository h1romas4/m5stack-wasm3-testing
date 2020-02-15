#include "esp_system.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <M5Stack.h>

#include "wasm3.h"
#include "m3_env.h"
#include "m3_api_defs.h"

#include "app.wasm.h"

#define FATAL(msg, ...) { M5.Lcd.printf("Fatal: " msg "\n", ##__VA_ARGS__); return; }

// link arduino library
m3ApiRawFunction(m3_arduino_random) {
    m3ApiReturnType (uint32_t)
    m3ApiGetArg     (uint32_t, max)
    m3ApiReturn     (random(max));
}

M3Result LinkArduino(IM3Runtime runtime) {
    IM3Module module = runtime->modules;
    const char* arduino = "arduino";

    m3_LinkRawFunction (module, arduino, "random", "i(i)",  &m3_arduino_random);

    return m3Err_none;
}

static void run_wasm(void)
{
    M3Result result = m3Err_none;

    uint8_t* wasm = (uint8_t*)build_app_wasm;
    uint32_t fsize = build_app_wasm_len - 1;

    IM3Environment env = m3_NewEnvironment ();
    if (!env) FATAL("m3_NewEnvironment failed");

    IM3Runtime runtime = m3_NewRuntime (env, 1024, NULL);
    if (!runtime) FATAL("m3_NewRuntime failed");

    IM3Module module;
    result = m3_ParseModule (env, &module, wasm, fsize);
    if (result) FATAL("m3_ParseModule: %s", result);

    result = m3_LoadModule (runtime, module);
    if (result) FATAL("m3_LoadModule: %s", result);

    // link arduino library
    result = LinkArduino (runtime);
    if (result) FATAL("LinkArduino %s", result);

    // function lookup
    IM3Function init;
    result = m3_FindFunction (&init, runtime, "init");
    if (result) FATAL("m3_FindFunction: %s", result);

    // call wasm
    const char* i_argv[3] = { "240", "240", NULL };
    result = m3_CallWithArgs (init, 2, i_argv);
    if (result) FATAL("m3_CallWithArgs: %s", result);

    // bitblt
    uint8_t* vram = (uint8_t*)(m3_GetMemory(runtime, 0, 0));
    M5.Lcd.pushImage(40, 0, 240, 240, vram, true);
}

// the setup routine runs once when M5Stack starts up
void setup(){

    // Initialize the M5Stack object
    M5.begin();

    // Run wasm3
    clock_t start = clock();
    run_wasm();
    clock_t end = clock();

    M5.Lcd.printf("\nWasm3 v" M3_VERSION " on ESP32, build " __DATE__ " " __TIME__ "\n\n");
    M5.Lcd.printf("Elapsed: %ld ms\n\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    M5.Lcd.printf("free memory: %d byte\n\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
}

// the loop routine runs over and over again forever
void loop() {
}
