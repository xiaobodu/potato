#/usr/bin/env bash

echo ">>> install"

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

if [ "$CXX" = "g++" ]; then sudo apt-get install -qq g++-4.8; fi
sudo apt-get install cppcheck valgrind libgles1-mesa-dev qt5-default ggcov
sudo pip install cpp-coveralls

#echo "||| check the gcov version"
#ggcov --version

echo "<<< install"
