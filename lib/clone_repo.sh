#!/bin/bash
# This script clones a git repository

# Define the repository URL
REPO_URL1="https://github.com/tenergyinnovation/tiny32_v3.git"
REPO_URL2="https://github.com/adafruit/Adafruit-ST7735-Library.git"
REPO_URL3="https://github.com/adafruit/Adafruit-GFX-Library.git"
REPO_URL4="https://github.com/adafruit/Adafruit_BusIO.git"
REPO_URL5="https://github.com/adafruit/Adafruit_ImageReader.git"
REPO_URL6="https://github.com/adafruit/SdFat.git"
REPO_URL7="https://github.com/adafruit/Adafruit_EPD.git"



# Define the target directory (optional)
TARGET_DIR="repository"

# Clone the repository
git clone $REPO_URL1
git clone $REPO_URL2
git clone $REPO_URL3
git clone $REPO_URL4
git clone $REPO_URL5
git clone $REPO_URL6
git clone $REPO_URL7




echo "****************************"
echo "* Success run clone script *"
echo "****************************"