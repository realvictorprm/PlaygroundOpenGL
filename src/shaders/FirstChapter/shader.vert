#version 330 core
layout (location = 0) in vec3 aPos;

uniform float globalTime;

void main()
{
    gl_Position = vec4(aPos.x + 0.5 * sin(globalTime * 2.), aPos.y + 0.5 * cos(2. * globalTime), aPos.z, 1.0);
}