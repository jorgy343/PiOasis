#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DIR="$DIR/compilers/aarch64-linux-gnu"

mkdir -p "$DIR/build/build-binutils"
mkdir -p "$DIR/build/build-gcc"

cd "$DIR/build/"

wget ftp://ftp.gnu.org/gnu/binutils/binutils-2.27.tar.bz2
tar -jxvf binutils-2.27.tar.bz2
rm binutils-2.27.tar.bz2

wget ftp://ftp.gnu.org/gnu/gcc/gcc-6.2.0/gcc-6.2.0.tar.bz2
tar -jxvf gcc-6.2.0.tar.bz2
rm gcc-6.2.0.tar.bz2

export PATH=$DIR/bin:$PATH

cd gcc-6.2.0/
./contrib/download_prerequisites

cd ../build-binutils/
../binutils-2.27/configure --target=aarch64-linux-gnu --prefix="$DIR" --with-sysroot --disable-nls --disable-werror --disable-multilib

make -j4
make install

cd ../build-gcc/
../gcc-6.2.0/configure --target=aarch64-linux-gnu --prefix="$DIR" --disable-nls --enable-languages=c,c++ --without-headers --disable-multilib

make -j4 all-gcc
make install-gcc

cd "$DIR/"
rm -rf build
