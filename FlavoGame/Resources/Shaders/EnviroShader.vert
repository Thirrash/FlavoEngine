#version 330 core
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 NormalVec;
layout (location = 2) in vec2 UVCoords;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 World;
uniform mat3 NormalMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 OutUVCoords;

void main()
{
    OutUVCoords = UVCoords;
	FragPos = vec3((World * vec4(VertexPosition, 1.0)).xyz);
	Normal  = NormalMatrix * NormalVec;
    gl_Position = Projection * View * World * vec4(VertexPosition, 1.0);
}