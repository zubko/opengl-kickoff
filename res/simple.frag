#version 330

smooth in vec4 theColor;

uniform float fragLoopDuration;
uniform float time;

out vec4 outputColor;

void main()
{
    float timeScale = 3.14159f * 2.0f / fragLoopDuration;

    float delta = sin(time * timeScale) * 0.5;
    vec4 color = theColor;
    color.r += delta;
    color.g += delta;
    color.b += delta;

    outputColor = color;
}
