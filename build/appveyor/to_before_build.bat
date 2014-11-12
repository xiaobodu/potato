echo ">>> before build"
git submodule init
git submodule update
mkdir out
cd out
mkdir bin
mkdir lib
mkdir msbuild
wget ftp://sourceware.org/pub/pthreads-win32/pthreads-w32-2-9-1-release.zip
unzip -oq pthreads-w32-2-9-1-release.zip -d pthreads-w32-2-9-1-release
cd ../code/external/zlib/
cmake -G "Visual Studio 11" ./
msbuild zlib.sln /p:Configuration=Release
cd ../libpng/
cmake -G "Visual Studio 11" -D PNG_DEBUG=FALSE -D PNG_SHARED=FALSE -D PNG_TESTS=FALSE -D ZLIB_INCLUDE_DIR=code/external/zlib -D ZLIB_LIBRARY=../../code/external/zlib/Release/zlibstatic.lib ./
cd ../../../build/
config-tcc.bat
cd ../out/msbuild/
cmake -G "Visual Studio 11" -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_CXX_COMPILER_ID=MSVC -D ZLIB_INCLUDE_DIR=code/external/zlib -D ZLIB_LIBRARY=../../code/external/zlib/Release/zlibstatic.lib ../../build/cmake
cd ../../
echo "<<< before build"
