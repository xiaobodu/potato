REM generate `config.h` for tiny c compiler
cd ../code/external/tinycc/win32
@set /p VERSION= < ..\VERSION
echo>..\config.h #define TCC_VERSION "%VERSION%"
cd ../../../../build
