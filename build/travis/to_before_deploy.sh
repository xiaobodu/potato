echo ">>> before deploy"

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
