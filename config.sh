mkdir build/make
mkdir out
mkdir out/bin
mkdir out/lib

cd build/make
cmake -G Unix\ Makefiles ../cmake/
cd ../..
