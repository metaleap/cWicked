#!/usr/bin/bash
set -e

# pre-requisite: you ran `./setup_wicked.sh` which creates the `./.wi` dir

thisScriptsFilePath="$(readlink --canonicalize-existing "$0")"
thisScriptsDirPath="$(dirname "$thisScriptsFilePath")"
cd $thisScriptsDirPath

rm -rf .cache
rm -rf .build
mkdir .build

mkdir .build/debug
mkdir .build/debug/shaders
cp .wi/.build_RelWithDebInfo/WickedEngine/libdxcompiler.so .build/debug/
meson setup --native-file meson_native.ini .build/debug

mkdir .build/release_gcc
mkdir .build/release_gcc/shaders
cp .wi/.build_RelWithDebInfo/WickedEngine/libdxcompiler.so .build/release_gcc/
meson setup -Dbuildtype=release -Dprefer_static=true .build/release_gcc

mkdir .build/release_clang
mkdir .build/release_clang/shaders
cp .wi/.build_RelWithDebInfo/WickedEngine/libdxcompiler.so .build/release_clang/
CC=clang CXX=clang++ meson setup -Dbuildtype=release -Dprefer_static=true .build/release_clang

cp .build/debug/compile_commands.json .
