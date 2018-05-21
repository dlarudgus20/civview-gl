#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 projMatrix;
uniform mat4 vmMatrix;

void main()
{
    vec4 pos = vec4(position, 1.0);
    gl_Position = projMatrix * vmMatrix * pos;
}
