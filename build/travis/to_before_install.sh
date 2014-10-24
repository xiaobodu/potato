echo ">>> before install"

if [ -z $TRAVIS_TAG ]; then
if [ "$DEPLOY_RELEASE"x != "true"x ]; then
  exit
fi
else
if [ "$RUN_COVERALLS"x != "true"x ]; then
  exit
fi
fi

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo apt-get update

echo "<<< before install"
