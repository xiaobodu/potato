echo ">>> install"

sudo apt-get install cppcheck valgrind libgles1-mesa-dev qt5-default

if [ "$RUN_COVERALLS"x = "true"x ]; then
  sudo pip install cpp-coveralls
else
  echo "< don't install anything for coveralls >"
fi

echo "<<< install"
