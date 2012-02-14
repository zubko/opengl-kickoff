//
//  Shader.h
//  HelloSDL
//
//  Created by Alexander Zubko on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef HelloSDL_Shader_h
#define HelloSDL_Shader_h

class Shader {
public:
    Shader();
    
    bool InitWithName(const string &name);
    void Use();
    void Leave();
    
    bool AddUniform(const string &name);
    void SetUniform1f(const string &name, GLfloat v0);
    void SetUniform2f(const string &name, GLfloat v0, GLfloat v1);
    void SetUniform3f(const string &name, GLfloat v0, GLfloat v1, GLfloat v2);
    void SetUniformMatrix4fv(const string &name, GLsizei count, GLboolean transpose, const GLfloat *value);
    
private:
    GLuint program_;
    map<string, GLint> uniforms_;
    string name_;
};

#endif
