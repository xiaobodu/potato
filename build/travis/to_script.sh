if [ -z $TRAVIS_TAG ]; then
if [ "$RUN_COVERALLS"x = "true"x ]; then
  cd out/make/
  make
  cd ../../
fi
elif [ "$DEPLOY_RELEASE"x = "true"x ]; then
  cd out/make/
  make
  cd ../../
fi
