# m5stack-wasm3-testing

WebAssembly interpreter [Wasm3](https://github.com/wasm3/wasm3) on M5Stack.

![](https://github.com/h1romas4/m5stack-wasm3-testing/blob/master/docs/images/m5stack-wasm3-01.jpg)

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

m5stack-wasm3-fib32/main/main.cpp

```
// const char* i_argv[2] = { "24", NULL }; // TODO: It will be reset.
const char* i_argv[2] = { "16", NULL };
result = m3_CallWithArgs (f, 1, i_argv);
```

```
Total sizes:
 DRAM .data size:    7496 bytes
 DRAM .bss  size:    7280 bytes
Used static DRAM:   14776 bytes ( 109804 available, 11.9% used)
Used static IRAM:  114268 bytes (  16804 available, 87.2% used)
      Flash code:  172466 bytes
    Flash rodata:  131136 bytes
Total image size:~ 425366 bytes (.bin may be padded larger)
```

## Dependencies

|name|version|
|-|-|
|[Wasm3](https://github.com/wasm3/wasm3)|0.4.6|
|[esp-idf](https://docs.espressif.com/projects/esp-idf/en/v3.2.3/get-started/index.html)|v3.2.3|
|[esp32-arduino](https://github.com/espressif/arduino-esp32)|1.0.4|
|[m5stack](https://github.com/m5stack/M5Stack)|0.2.9|
