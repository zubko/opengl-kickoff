//
//  Utils.h
//  HelloSDL
//
//  Created by Alexander Zubko on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef HelloSDL_Utils_h
#define HelloSDL_Utils_h

#if (!defined (NDEBUG) || defined (DEBUG))
    #define SDL_CHECK_ERROR checkSDLError(__FILE__, __LINE__)
    #define OPENGL_CHECK_ERROR checkOGLError(__FILE__, __LINE__)
    #define CHECK_RESULT(code) do {if (!(code)) return false;} while(0)
    #define GL(command) do {command; OPENGL_CHECK_ERROR;} while(0)
#else
    #define SDL_CHECK_ERROR 
    #define OPENGL_CHECK_ERROR
    #define CHECK_RESULT(code) (code)
    #define GL(code) (code)
#endif

void checkSDLError(const char *file, int line);
void checkOGLError(const char *file, int line);

#define ARRAY_COUNT(array) (sizeof(array)/sizeof(array[0]))


#endif
