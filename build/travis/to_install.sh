echo ">>> install"

if [ -z "$TRAVIS_TAG"x ]; then
if [ "$RUN_COVERALLS"x = "true"x ]; then
  sudo apt-get install cppcheck valgrind libgles1-mesa-dev qt5-default
  sudo pip install cpp-coveralls
fi
else
  echo "< don't install anything for coveralls >"
fi

echo "<<< install"
