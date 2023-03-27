#!/bin/bash

# This script takes all necessary steps to install the three libraries required by Twilio on the host machine:
# OpenSSL, zlib, and curl. If everything succeeds, then you will only need to run this script once.

# Make this script exit immediately if any commands fail.
set -e

# *****************************************************************************
# Make folder to store Twilio dependency tarballs and their extracted contents.
# *****************************************************************************
downloads_folder="$HOME/twilio_dependency_downloads"

echo "This script will install the needed libraries for Twilio (OpenSSL, zlib, and curl) for arm-linux-gnueabihf FROM THE SOURCE CODE (i.e., it must build everything)."
echo "This script will TAKE A WHILE to complete and you will be REQUIRED TO ENTER YOUR SUDO PASSWORD AT MULTIPLE POINTS (which will obviously stall the script's execution until you enter your password). IF ANY STEPS FAIL, save the script's output and let Ben know. The script will say in all caps if the installation succeeded at the end."
echo "(sleeping 5 seconds so this message is seen...)"
sleep 5
echo ""

echo "Creating folder to store Twilo dependency downloads at '$downloads_folder'."
mkdir -p $downloads_folder
cd $downloads_folder
echo ""

# ***************************************
# Install OpenSSL for arm-linux-gnueabihf
# ***************************************
openssl_downloads_folder=openssl-3.0.8
echo "Downloading OpenSSL source code (this may take a while)..."
wget https://www.openssl.org/source/$openssl_downloads_folder.tar.gz
echo ""

echo "Extracting '$openssl_downloads_folder.tar.gz' tarball.."
tar xf $openssl_downloads_folder.tar.gz
cd $openssl_downloads_folder
echo ""

echo "Executing install OpenSSL step 1: Configuration..."
./Configure linux-generic32 --prefix=/usr/arm-linux-gnueabihf/openssl --cross-compile-prefix=arm-linux-gnueabihf-
echo ""

echo "Executing install OpenSSL step 2: Build..."
make
echo ""

echo "Executing install OpenSSL step 3: Install..."
sudo make install
echo ""
echo ""

# ************************************
# Install zlib for arm-linux-gnueabihf
# ************************************
cd $downloads_folder
zlib_downloads_folder=zlib-1.2.13
echo "Downloading zlib source code (this may take a while)..."
wget https://zlib.net/$zlib_downloads_folder.tar.gz
echo ""

echo "Extracting '$zlib_downloads_folder.tar.gz' tarball.."
tar xf $zlib_downloads_folder.tar.gz
cd $zlib_downloads_folder
echo ""

echo "Executing install zlib step 1: Configuration..."
CROSS_PREFIX=arm-linux-gnueabihf- ./configure --prefix=/usr/arm-linux-gnueabihf/zlib
echo ""

echo "Executing install zlib step 2: Build..."
make
echo ""

echo "Executing install zlib step 3: Install..."
sudo make install
echo ""
echo ""

# ************************************
# Install curl for arm-linux-gnueabihf
# ************************************
cd $downloads_folder
curl_downloads_folder=curl-7.88.1
echo "Downloading curl source code (this may take a while)..."
wget https://curl.se/download/$curl_downloads_folder.tar.gz
echo ""

echo "Extracting '$curl_downloads_folder.tar.gz' tarball.."
tar xf $curl_downloads_folder.tar.gz
cd $curl_downloads_folder
echo ""

echo "Executing install curl step 1: Configuration..."
./configure --host=arm-linux-gnueabihf --prefix=/usr/arm-linux-gnueabihf/curl --with-openssl=/usr/arm-linux-gnueabihf/openssl --with-zlib=/usr/arm-linux-gnueabihf/zlib --without-brotli
echo ""

echo "Executing install curl step 2: Build..."
make
echo ""

echo "Executing install curl step 3: Install..."
sudo make install
echo ""
echo ""

# **********************
# Installation complete.
# **********************
echo "TWILIO DEPENDENCY INSTALLATION SUCCEEDED!"
