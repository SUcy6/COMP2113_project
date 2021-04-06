#!/bin/bash

cd ~
mkdir group90

mkdir ~/repos
cd ~/repos

git clone https://github.com/mirror/ncurses.git
cd ncurses

./configure --prefix ~/group90 --enable-widec --with-pthread

make -j
make -j install
