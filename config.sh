mkdir -p build/make
mkdir -p out
mkdir -p out/bin
mkdir -p out/lib

cd build/make/
cmake -D CMAKE_BUILD_TYPE=Debug ../cmake/
cd ../../
