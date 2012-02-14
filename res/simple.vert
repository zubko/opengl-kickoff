#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
uniform float loopDuration;
uniform float time;
uniform vec3 offset;
uniform mat4 perspectiveMatrix;

smooth out vec4 theColor;

void main()
{
    float timeScale = 3.14159f * 2.0f / loopDuration;    
    float currTime = mod(time, loopDuration);
    vec2 animOffset = vec2(cos(currTime * timeScale) * 0.5f,
                            sin(currTime * timeScale) * 0.5f);
    
    vec4 cameraPos = position;
    cameraPos.xyz += offset;
    cameraPos.xy += animOffset;

    gl_Position = perspectiveMatrix * cameraPos;
    theColor = color;
}
