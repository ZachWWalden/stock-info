#!/usr/bin/sh
if [ $1 != ""]; then
	mkdir /home/$1/.local/bin
	#libjsoncpp-dev
	#libcurl4
	sudo apt install libjsoncpp-dev libcurl4 &
	cd stock-info &
	make &
	chmod +x stock-info &
	cp stock-info /home/$1/.local/bin/
else
	echo "Please enter your username"
fi
