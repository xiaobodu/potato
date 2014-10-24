echo ">>> before deploy"

if [ -z "$TRAVIS_TAG"x ]; then
if [ "$DEPLOY_RELEASE"x != "true"x ]; then
  exit
fi
else
if [ "$RUN_COVERALLS"x != "true"x ]; then
  exit
fi
fi

if [ "$DEPLOY_RELEASE"x = "true"x ]; then
  cd out
  mkdir -p potato
  mkdir -p potato/bin
  cp -r ./bin/* potato/bin/
  cp -r ../data potato/
  tar -czf potato.$TRAVIS_TAG.$TRAVIS_OS_NAME.tar.gz ./potato/
  cd ../
else
  echo "< don't deploy anything >"
fi

echo "<<< before deploy"
