//
//  Utils.cpp
//  HelloSDL
//
//  Created by Alexander Zubko on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "common.h"

#include "Utils.h"

void checkSDLError(const char *file, int line)
{
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: file %s @ line %d: %s\n", 
               file, line, error);
		SDL_ClearError();
	}
}

void checkOGLError(const char *file, int line)
{
    GLenum glErr;
    
    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("OpenGL Error: file %s @ line %d: %s\n",
               file, line, gluErrorString(glErr));
    }
}
