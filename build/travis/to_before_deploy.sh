echo ">>> before deploy"

if [ "$DEPLOY_RELEASE"x = "true"x ]; then
  cd out
  mkdir -p potato
  mkdir -p potato/bin
  cp -r ./bin/* potato/bin/
  cp -r ../data potato/
  tar -czf potato.$TRAVIS_TAG.$TRAVIS_OS_NAME.tar.gz ./potato/
  cd ../
fi

echo "<<< before deploy"
