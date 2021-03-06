echo ">>> before build"
cd ../../
git submodule init
git submodule update
mkdir out
cd out
mkdir msbuild
REM wget ftp://sourceware.org/pub/pthreads-win32/pthreads-w32-2-9-1-release.zip
REM unzip -oq pthreads-w32-2-9-1-release.zip -d pthreads-w32-2-9-1-release
cd ../code/external/zlib/
cmake -G "Visual Studio 12" ./
msbuild zlib.sln /p:Configuration=Release
cd ../libpng/
echo "||| generate the libpng solution"
cmake -G "Visual Studio 12" -D PNG_DEBUG=FALSE -D PNG_SHARED=FALSE -D PNG_TESTS=FALSE -D ZLIB_INCLUDE_DIR=code/external/zlib -D ZLIB_LIBRARY=../../code/external/zlib/Release/zlibstatic.lib ./
cd ../../../build/
call config-tcc.bat
cd ../out/msbuild/
echo "||| generate the potato solution"
cmake -G "Visual Studio 12" -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_CXX_COMPILER_ID=MSVC -D ZLIB_INCLUDE_DIR=code/external/zlib -D ZLIB_LIBRARY=../../code/external/zlib/Release/zlibstatic.lib ../../build/cmake
cd ../../
cd build/appveyor/
echo "<<< before build"
