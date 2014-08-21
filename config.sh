mkdir build/make
mkdir out
mkdir out/bin
mkdir out/lib

cd build/make
cmake -G Unix\ Makefiles -D CMAKE_BUILD_TYPE=Debug ../cmake/
cd ../..
