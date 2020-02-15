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

```
git clone --recursive https://github.com/h1romas4/m5stack-wasm3-testing.git
cd m5stack-wasm3-testing
# This repository includes eps-idf v3.2.3
export IDF_PATH=$(pwd)/esp-idf
```

### m5stack-wasm3-fib3

```
cd m5stack-wasm3-fib32
make flash monitor
```

### m5stack-wasm3-bitblt

```
cd m5stack-wasm3-bitblt
cd wasm
npm install
npm run asbuild
cd ..
make flash monitor
```

## Dependencies

|name|version|
|-|-|
|[Wasm3](https://github.com/wasm3/wasm3)|0.4.6|
|[esp-idf](https://docs.espressif.com/projects/esp-idf/en/v3.2.3/get-started/index.html)|v3.2.3|
|[esp32-arduino](https://github.com/espressif/arduino-esp32)|1.0.4|
|[m5stack](https://github.com/m5stack/M5Stack)|0.2.9|
