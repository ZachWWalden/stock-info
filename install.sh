#!/usr/bin/sh

#libjsoncpp-dev
#libcurl4
sudo apt install libjsoncpp-dev libcurl4 libcurl4-openssl-dev &&
cd stock-info &&
make &&
chmod +x stock-info &&
sudo cp stock-info /home/$USER/.local/bin/
