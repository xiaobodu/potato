mkdir -p ../out
mkdir -p ../out/bin
mkdir -p ../out/lib
mkdir -p ../out/make

cd ../out/make/
cmake -D CMAKE_BUILD_TYPE=Debug ../../build/cmake/
cd ../../build/
