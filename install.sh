#!/usr/bin/sh
mkdir /home/$USER/.local/ &&
mkdir /home/$USER/.local/bin &&
#libjsoncpp-dev
#libcurl4
sudodo apt install libjsoncpp-dev libcurl4 libcurl4-openssl-dev &&
cd stock-info &&
make &&
chmod +x stock-info &&
cp stock-info /home/$USER/.local/bin/
