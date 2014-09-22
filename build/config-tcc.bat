cd ../code/external/tinycc/win32
@set /p VERSION= < ..\VERSION
echo>..\config.h #define TCC_VERSION "%VERSION%"
cd ../../../../build