#!/bin/bash
sudo apt-get install libssl-dev openssl git miniupnpc libdb-dev libdb++-dev libleveldb-dev build-essential libgmp-dev autoconf libtool libboost-all-dev libcurl4-openssl-dev git libboost-chrono-dev libboost-filesystem-dev libboost-program-options-dev libboost-system-dev libboost-test-dev libboost-thread-dev libprotobuf-dev protobuf-compiler libqrencode-dev -y
make -f makefile.unix
