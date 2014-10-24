echo ">>> install"

if [ -z "$TRAVIS_TAG"x ]; then
if [ "$DEPLOY_RELEASE"x != "true"x ]; then
  exit
fi
else
if [ "$RUN_COVERALLS"x != "true"x ]; then
  exit
fi
fi

sudo apt-get install cppcheck valgrind libgles1-mesa-dev qt5-default
sudo pip install cpp-coveralls

echo "<<< install"
