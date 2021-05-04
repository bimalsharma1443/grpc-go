#!/bin/bash
export MY_INSTALL_DIR=$HOME/.local
mkdir -p $MY_INSTALL_DIR
export PATH="$MY_INSTALL_DIR/bin:$PATH"
mkdir -p cmake/build
pushd cmake/build
make -j
