#version 330 core
#define MAX_NO_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 OutUVCoords;
out vec4 FragColor;

uniform sampler2D Texture;
uniform vec3 ViewPos;

struct MaterialProperties {
	vec4 ObjectColor;
	
	vec3 Diffuse;
	vec3 Ambient;
	vec3 Specular;
	float Shininess;
};

struct DirectionalLight {
	vec3 Direction;
	vec3 Color;
};

struct PointLight {
	vec3 Position;
	vec3 Color;
    
    float Constant;
    float Linear;
    float Quadratic;  
};

vec3 CalcDirLight(DirectionalLight light, MaterialProperties prop, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.Direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), prop.Shininess);

    vec3 ambient  = 1.0 * prop.Ambient  * vec3(texture(Texture, OutUVCoords));
    vec3 diffuse  = 1.0 * prop.Diffuse  * diff * vec3(texture(Texture, OutUVCoords));
    vec3 specular = 1.0 * prop.Specular * spec * vec3(texture(Texture, OutUVCoords));
    return light.Color * (ambient + diffuse + specular);
}  

//Params
uniform MaterialProperties MatProp;
uniform DirectionalLight DirLight;
//uniform PointLight PointLights[MAX_NO_POINT_LIGHTS];

void main() {
   FragColor = MatProp.ObjectColor * vec4(CalcDirLight(DirLight, MatProp, normalize(Normal), normalize(ViewPos - FragPos)), 1.0);
}

