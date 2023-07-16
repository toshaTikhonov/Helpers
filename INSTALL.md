# Install Helpers



## CMake - Multi architecture

Вы можете собрать библиотеку Helpers с помощью CMake, пример:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make && sudo make install
```

Есть следующие опции для сборки CMake:
- `-DBUILD_STATIC=[on|off]` (default `off`): сборка статической библиотеки, по умолчанию будет динамическая
- `-DBUILD_HELPERS_TESTING=[on|off]` (default `off`): Сборка тестов (пока не поддерживается)
- `-DBUILD_HELPERS_DOCUMENTATION=[on|off]` (default `off`): Сборка документации, с помощью doxygen
- `-DCMAKE_BUILD_TYPE=[Debug|Release]` (default `Release`): компиляция с отладочной информацией
