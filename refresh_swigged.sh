#!/usr/bin/bash
set -e

thisScriptsFilePath="$(readlink --canonicalize-existing "$0")"
thisScriptsDirPath="$(dirname "$thisScriptsFilePath")"
cd $thisScriptsDirPath



cd src
# rm -f ./swigged_cwicked_wrap.*
swig -c++ -c -nocxx -noexcept -fastdispatch -fvirtual -templatereduce -std=c++17 ./swigged_cwicked.swg
