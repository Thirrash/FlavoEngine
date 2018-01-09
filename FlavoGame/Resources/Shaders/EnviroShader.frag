#version 330 core
#define MAX_NO_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 OutUVCoords;
out vec4 FragColor;

uniform samplerCube skybox;
uniform vec3 ViewPos;

struct MaterialProperties {
	float Reflect;
	float Refract;
};

//Params
uniform MaterialProperties MatProp;

void main() {
	float ratio = 1.0 / MatProp.Refract;
	vec3 I = normalize(FragPos - ViewPos);
	vec3 R;
	if (MatProp.Reflect > 0.1) {
		R = reflect(I, normalize(Normal)) * MatProp.Reflect;
	} else {
		R = refract(I, normalize(Normal), ratio);
	}

    FragColor = vec4(clamp(texture(skybox, R).rgb, 0.0, 1.0), 1.0);
}

