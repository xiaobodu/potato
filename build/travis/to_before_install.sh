echo ">>> before install"
if [ -z $TRAVIS_TAG ]; then
if [ "$RUN_COVERALLS"x = "true"x ]; then
sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo apt-get update
fi
elif [ "$DEPLOY_RELEASE"x = "true"x ]; then
sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo apt-get update
fi
echo "<<< before install"
