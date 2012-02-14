//
//  Shader.cpp
//  HelloSDL
//
//  Created by Alexander Zubko on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "common.h"

#include "Shader.h"

GLuint CreateShader(GLenum shaderType, const std::string &shaderFile);
GLuint CreateProgram(GLuint vertShader, GLuint fragShader);

#ifndef NDEBUG
    #define CHECK_UNIFORM do {if (uniforms_.find(name) == uniforms_.end()) {\
        fprintf(stderr, "Error: Can't find uniform '%s' in shader '%s'!\n", name.c_str(), name_.c_str());\
    }} while (0)
#else 
    #define CHECK_UNIFORM
#endif

Shader::Shader() 
: program_(0) 
{
    
}

bool Shader::InitWithName(const string &name) {
    name_ = name;
    
    GLuint vert_shader = CreateShader(GL_VERTEX_SHADER, name + ".vert");
    if (vert_shader == 0) {
        return false;
    }
    
    GLuint frag_shader = CreateShader(GL_FRAGMENT_SHADER, name + ".frag");
    if (frag_shader == 0) {
        glDeleteShader(vert_shader);
        return false;
    };
    
    vector<GLuint> shaders;
    program_ = CreateProgram(vert_shader, frag_shader);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    return program_ != 0;
}

void Shader::Use() {
    glUseProgram(program_);
    OPENGL_CHECK_ERROR;
}

void Shader::Leave() {
    glUseProgram(0);
    OPENGL_CHECK_ERROR;
}

bool Shader::AddUniform(const string &name) {
    GLint location = glGetUniformLocation(program_, name.c_str());
    OPENGL_CHECK_ERROR;
    if (location > -1) {
        uniforms_[name] = location;
        return true;
    } else {
        fprintf(stderr, "Error: Can't find uniform '%s' in shader '%s'!\n", name.c_str(), name_.c_str());
        return false;
    }
}

void Shader::SetUniform1f(const string &name, GLfloat v0) {
    CHECK_UNIFORM;
    glUniform1f(uniforms_[name], v0);
    OPENGL_CHECK_ERROR;
}

void Shader::SetUniform2f(const string &name, GLfloat v0, GLfloat v1) {
    CHECK_UNIFORM;
    glUniform2f(uniforms_[name], v0, v1);
    OPENGL_CHECK_ERROR;
}

void Shader::SetUniform3f(const string &name, GLfloat v0, GLfloat v1, GLfloat v2) {
    CHECK_UNIFORM;
    GL(glUniform3f(uniforms_[name], v0, v1, v2));
}

void Shader::SetUniformMatrix4fv(const string &name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CHECK_UNIFORM;
    glUniformMatrix4fv(uniforms_[name], count, transpose, value);
    OPENGL_CHECK_ERROR;
}

#pragma mark - Creation functions

GLuint CreateShader(GLenum shaderType, const std::string &shaderFile)
{
    SDL_RWops *source = SDL_RWFromFile(shaderFile.c_str(), "r");
    int size = SDL_RWseek(source, 0, RW_SEEK_END);
    char *strFileData = new char[size+1];
    strFileData[size] = 0;
    SDL_RWseek(source, 0, RW_SEEK_SET);
    SDL_RWread(source, strFileData, 1, size);
    SDL_CHECK_ERROR;
    //fprintf(stdout, "======\nSHADER: \n%s\n======\n", strFileData);
    
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const char**)&strFileData, &size);
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        const char *strShaderType = NULL;
        switch(shaderType)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        
        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }
    
    delete [] strFileData;
    SDL_RWclose(source);
	return shader;
}

GLuint CreateProgram(GLuint vertShader, GLuint fragShader)
{
    GLuint program = glCreateProgram();
    
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    
    return program;
}
