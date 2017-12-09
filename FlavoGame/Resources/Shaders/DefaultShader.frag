#version 330 core

in vec2 OutUVCoords;
out vec4 FragColor;

uniform sampler2D Texture;
uniform vec4 ObjectColor;

void main()
{
   FragColor = ObjectColor * texture(Texture, OutUVCoords);
}
