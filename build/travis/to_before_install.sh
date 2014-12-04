#/usr/bin/env bash

echo ">>> before install"

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

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
if [ "$CXX" == "g++" ]; then sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test; fi
sudo apt-get update -qq

echo "<<< before install"
