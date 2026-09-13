//
//  WebGLCompat.h
//
//  Small compatibility shims needed to run this project's OpenGL
//    code through Emscripten's legacy GL emulation (WebGL), which
//    does not implement every fixed-function entry point that
//    desktop GLUT/OpenGL provide.
//

#pragma once

void drawWireSphere (double radius, int slices, int stacks);
