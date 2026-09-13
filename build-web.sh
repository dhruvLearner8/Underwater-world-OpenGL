#!/bin/bash
# Builds the WebAssembly/WebGL version of the game and copies it into docs/
# for GitHub Pages. Requires the Emscripten SDK (emsdk) on PATH -
# https://emscripten.org/docs/getting_started/downloads.html
#
# LEGACY_GL_EMULATION requires the classic (pre-6.x) emscripten toolchain -
# newer versions dropped display-list/glut-shape/material emulation. Tested
# against emsdk 3.1.61.

set -e
cd "$(dirname "$0")"

em++ -std=c++14 -Wno-deprecated-declarations -I. -IObjLibrary \
  *.cpp ObjLibrary/*.cpp \
  -lglut -lGL \
  -s LEGACY_GL_EMULATION=1 \
  -s INITIAL_MEMORY=268435456 \
  -s GL_MAX_TEMP_BUFFER_SIZE=67108864 \
  --preload-file Resources \
  -o underwater.html

mkdir -p docs
cp underwater.html docs/index.html
cp underwater.js underwater.wasm underwater.data docs/

echo "Built. Serve docs/ locally with: python3 -m http.server -d docs 8000"
