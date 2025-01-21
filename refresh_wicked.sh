#!/usr/bin/bash
set -e
wiVer="0.71.661"

thisScriptsFilePath="$(readlink --canonicalize-existing "$0")"
thisScriptsDirPath="$(dirname "$thisScriptsFilePath")"
cd $thisScriptsDirPath



### clean up, fetch zip, extract zip:

# rm -rf .wi
# rm -rf WickedEngine*
# rm -f wi_src.zip
# wget -O wi_src.zip https://github.com/turanszkij/WickedEngine/archive/refs/tags/v$wiVer.zip
# unzip wi_src.zip
# rm -f wi_src.zip
# mv WickedEngine-$wiVer .wi



### build WickedEngine twice:

cd .wi

rm -rf .build_RelWithDebInfo
mkdir .build_RelWithDebInfo
cd .build_RelWithDebInfo
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DWICKED_PIC=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make
cp compile_commands.json ../compile_commands.json
cd ..

rm -rf .build_Release
mkdir .build_Release
cd .build_Release
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make
cd ..

cd ..
