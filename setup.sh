#!/bin/bash

sudo apt-get update
sudo apt-get install -y libsdl-gfx1.2-dev libsdl1.2-dev libsdl-mixer1.2-dev
sudo apt-get install -y libsdl-ttf2.0-dev libglib2.0-dev libxml2-dev
sudo apt-get install -y libsdl-image1.2-dev

sudo dpkg -i ./lib/libmlv0_2.0.2-1_amd64.deb ./lib/libmlv0-dev_2.0.2-1_amd64.deb
sudo apt-get install build-essential

sudo apt update
sudo apt install python3
sudo apt install python3-pip

sudo apt install gdb