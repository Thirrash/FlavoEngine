#version 330 core

in vec3 OutVertexColor;
in vec2 OutUVCoords;
out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
   FragColor = texture(Texture, OutUVCoords) * vec4(OutVertexColor.x, OutVertexColor.y, OutVertexColor.z, 1.0);
}
