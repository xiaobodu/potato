echo ">>> script"

if [ -z "$TRAVIS_TAG"x ]; then
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

cd out/make/
make
cd ../../

echo "<<< script"
