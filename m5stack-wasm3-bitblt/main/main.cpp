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

IM3Environment env;
IM3Runtime runtime;
IM3Module module;
IM3Function draw;

const char* i_argv[3] = { "240", "240", NULL };

static void run_wasm(void)
{
    M3Result result = m3Err_none;

    uint8_t* wasm = (uint8_t*)build_app_wasm;
    uint32_t fsize = build_app_wasm_len - 1;

    env = m3_NewEnvironment ();
    if (!env) FATAL("m3_NewEnvironment failed");

    runtime = m3_NewRuntime (env, 1024, NULL);
    if (!runtime) FATAL("m3_NewRuntime failed");

    result = m3_ParseModule (env, &module, wasm, fsize);
    if (result) FATAL("m3_ParseModule: %s", result);

    result = m3_LoadModule (runtime, module);
    if (result) FATAL("m3_LoadModule: %s", result);

    // link arduino library
    result = LinkArduino (runtime);
    if (result) FATAL("LinkArduino %s", result);

    // function lookup
    result = m3_FindFunction (&draw, runtime, "draw");
    if (result) FATAL("m3_FindFunction: %s", result);
}

// the setup routine runs once when M5Stack starts up
void setup(){

    // Initialize the M5Stack object
    M5.begin();

    // Run wasm3
    clock_t start = clock();
    run_wasm();
    clock_t end = clock();
}

// the loop routine runs over and over again forever
void loop() {
    M3Result result = m3Err_none;

    // call wasm
    result = m3_CallWithArgs (draw, 2, i_argv);
    if (result) FATAL("m3_CallWithArgs: %s", result);

    // bitblt
    uint8_t* vram = (uint8_t*)(m3_GetMemory(runtime, 0, 0));
    M5.Lcd.pushImage(40, 0, 240, 240, vram, true);
}
