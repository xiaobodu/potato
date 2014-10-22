./out/bin/t001
coveralls --exclude build/ --exclude data/ --exclude doc/ --exclude code/external/ --exclude out/make/external/ --exclude out/make/CMakeFiles/ --gcov-options '\-lp'
#valgrind --leak-check=yes out/bin/test
