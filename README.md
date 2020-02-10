# m5stack-wasm3-testing

WebAssembly interpreter [wasm3](https://github.com/wasm3/wasm3) on M5Stack.

## Require

* M5Stack
* [esp32-idf toolchain setup](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html#setup-toolchain)

```
$ xtensa-esp32-elf-gcc -v
gcc version 5.2.0 (crosstool-NG crosstool-ng-1.22.0-80-g6c4433a)
```

## Build

**Compile**

```
git clone --recursive https://github.com/h1romas4/m5stack-wasm3-testing.git
cd m5stack-wasm3-testing
# This repository includes eps-idf v3.2.3
export IDF_PATH=$(pwd)/esp-idf
cd m5stack-wasm3-fib32
make flash monitor
```

## ToDo

* [Performance / Wasm3 on MCUs](https://github.com/wasm3/wasm3/blob/master/docs/Performance.md#wasm3-on-mcus)

M5Stack stack overflow? (ESP32 is not support TCO yet.)

m5stack-wasm3-fib32/main/main.cpp

```
// const char* i_argv[2] = { "24", NULL };
const char* i_argv[2] = { "16", NULL };
result = m3_CallWithArgs (f, 1, i_argv);
```

## Dependencies

|name|version|
|-|-|
|[esp-idf](https://docs.espressif.com/projects/esp-idf/en/v3.2.3/get-started/index.html)|v3.2.3|
|[esp32-arduino](https://github.com/espressif/arduino-esp32)|1.0.4|
|[m5stack](https://github.com/m5stack/M5Stack)|0.2.9|
|[wasm3](https://github.com/wasm3/wasm3)|0.4.6|
