echo ">>> after success"

if [ "$TRAVIS_TAG" ]; then
if [ "$DEPLOY_RELEASE"x = "true"x ]; then
  VALID=ok
fi
else
if [ "$RUN_COVERALLS"x = "true"x ]; then
  VALID=ok
fi
fi

if [ "$VALID"x != "ok"x ]; then
  exit
fi

if [ "$RUN_COVERALLS"x = "true"x ]; then
  build/run_test.sh
  coveralls --exclude build/ --exclude data/ --exclude doc/ --exclude code/external/ --exclude out/make/external/ --exclude out/make/CMakeFiles/ --gcov-options '\-lp'
else
  echo "< don't run anything for coveralls >"
fi
#valgrind --leak-check=yes out/bin/test

echo "<<< after success"
