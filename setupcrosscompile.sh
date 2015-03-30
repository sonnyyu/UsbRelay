#!/bin/bash
BACKPATH=$PATH
export BACKPATH
STAGING_DIR=~/OpenWrt-SDK-ar71xx-for-linux-i486-gcc-4.6-linaro_uClibc-0.9.33.2/staging_dir
export STAGING_DIR
TOOLCHAIN_DIR=$STAGING_DIR/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2
PATH=$TOOLCHAIN_DIR/bin:$PATH
export PATH
TARGET_DIR=$STAGING_DIR/target-mips_r2_uClibc-0.9.33.2
CFLAGS=$TARGET_DIR/usr/include
export CFLAGS
LDFLAGS=$TARGET_DIR/usr/lib
export LDFLAGS
#LD_LIBRARY_PATH=$LDFLAGS
#export LD_LIBRARY_PATH
