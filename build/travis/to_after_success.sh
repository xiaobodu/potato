#/usr/bin/env bash

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

# run command with exit error-code
set -e

if [ "$RUN_COVERALLS"x = "true"x ]; then
  sudo ln -s -f /usr/bin/gcov-4.8 /usr/bin/gcov
  build/linux-run-demo.sh
  coveralls --exclude build/ --exclude data/ --exclude doc/ --exclude code/external/ --exclude out/make/external/ --exclude out/make/CMakeFiles/ --gcov-options '\-lp'
else
  echo "< don't run anything for coveralls >"
fi
#valgrind --leak-check=yes out/bin/demo

echo "<<< after success"
