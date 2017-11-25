#version 330 core
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 UVCoords;

uniform mat4 WorldViewProjection;

out vec2 OutUVCoords;

void main()
{
    OutUVCoords = UVCoords;
    gl_Position = WorldViewProjection * vec4(VertexPosition, 1.0);
}