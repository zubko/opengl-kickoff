#ifndef INC_HELLOSDL_COMMON_H
#define INC_HELLOSDL_COMMON_H

/* Include windows.h properly on Windows */
#if defined(WIN32) || defined(_WINDOWS)
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

/* SDL */
#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <OpenGL/glu.h>
#ifndef HELLO_MAGIC_MAIN
#  undef main
#endif

/* STL */
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

/* FRAMEWORK */
#include "Utils.h"

#endif
