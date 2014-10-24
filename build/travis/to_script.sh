echo ">>> script"

if [ -z $TRAVIS_TAG ]; then
if [ "$DEPLOY_RELEASE"x != "true"x ]; then
  exit
fi
else
if [ "$RUN_COVERALLS"x != "true"x ]; then
  exit
fi
fi

cd out/make/
make
cd ../../

echo "<<< script"
