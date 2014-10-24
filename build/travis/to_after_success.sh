echo ">>> after success"

if [ "$RUN_COVERALLS"x = "true"x ]; then
  build/run_test.sh
  coveralls --exclude build/ --exclude data/ --exclude doc/ --exclude code/external/ --exclude out/make/external/ --exclude out/make/CMakeFiles/ --gcov-options '\-lp'
else
  echo "< don't run anything for coveralls >"
fi
#valgrind --leak-check=yes out/bin/test

echo "<<< after success"
