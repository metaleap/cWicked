#!/usr/bin/bash
set -e

thisScriptsFilePath="$(readlink --canonicalize-existing "$0")"
thisScriptsDirPath="$(dirname "$thisScriptsFilePath")"
cd $thisScriptsDirPath



# pre-requisite: you ran `./refresh_wicked.sh` which creates the `./.wi` dir

rm -rf .cache
rm -rf .build
mkdir .build

wi_build_dir=".wi/.build_RelWithDebInfo"

mkdir .build/debug
mkdir .build/debug/shaders
cp $wi_build_dir/WickedEngine/libdxcompiler.so .build/debug/
meson setup -DWICKED_BUILD_DIR=$wi_build_dir --native-file meson_native.ini .build/debug

# wi_build_dir=".wi/.build_Release"

mkdir .build/release_gcc
mkdir .build/release_gcc/shaders
cp $wi_build_dir/WickedEngine/libdxcompiler.so .build/release_gcc/
meson setup -DWICKED_BUILD_DIR=$wi_build_dir -Dbuildtype=release -Dprefer_static=true .build/release_gcc

mkdir .build/release_clang
mkdir .build/release_clang/shaders
cp $wi_build_dir/WickedEngine/libdxcompiler.so .build/release_clang/
CC=clang CXX=clang++ meson setup -DWICKED_BUILD_DIR=$wi_build_dir -Dbuildtype=release -Dprefer_static=true .build/release_clang

cp .build/debug/compile_commands.json .
