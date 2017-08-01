#!/bin/bash
rm -rf ../build-sop
mkdir  ../build-sop
cd ../build-sop
/home/ccy/Syberos-Pdk/sdk/script/kchroot sb2 -t target-armv7tnhl-xuanwu -R qmake ../*.pro
/home/ccy/Syberos-Pdk/sdk/script/kchroot sb2 -t target-armv7tnhl-xuanwu -R make
/home/ccy/Syberos-Pdk/sdk/script/kchroot sb2 -t target-armv7tnhl-xuanwu -R buildpkg ../*.pro
