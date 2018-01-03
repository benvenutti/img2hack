#!/bin/bash -x

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
  sudo -E apt-get update -qq
  sudo -E apt-get install -y qt5-default libmagick++-dev
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  brew update
  brew install imagemagick --with-magick-plus-plus
  brew install qt@5.5
fi
