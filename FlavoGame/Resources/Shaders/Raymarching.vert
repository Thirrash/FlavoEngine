#version 330 core
layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 UVCoords;

out vec2 OutUVCoords;

void main()
{
    OutUVCoords = VertexPosition;
    gl_Position = vec4(VertexPosition.x, VertexPosition.y, 0.0, 1.0);
}