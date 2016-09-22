#!/bin/bash

mkdir newlib
cd newlib

wget -O newlib-source.tar.gz ftp://sources.redhat.com/pub/newlib/newlib-2.4.0.20160527.tar.gz
tar xzf newlib-source.tar.gz

rm newlib-source.tar.gz
mv newlib* newlib-source

newlib-source/configure --target aarch64-none-elf --disable-newlib-supplied-syscalls
make

rm -rfd ../source/newlib
mkdir -p ../source/newlib/include

cp aarch64-none-elf/newlib/libc.a ../source/newlib/
cp -r newlib-source/newlib/libc/include/* ../source/newlib/include/

cd ../
rm -rfd newlib
