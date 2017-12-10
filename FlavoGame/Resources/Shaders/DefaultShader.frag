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
	
	float Intensity;
	vec3 Color;
};

struct PointLight {
	vec3 Position;
	float Constant;
    float Linear;
    float Quadratic;  
	
	float Intensity;
	vec3 Color;
};

struct SpotLight {
	vec3 Position;
	vec3 Direction;
	float Cutoff;
	float OuterCutoff;
	
	float Intensity;
	vec3 Color;
};

vec3 CalcDirLight(DirectionalLight light, MaterialProperties prop, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.Direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), prop.Shininess);

    vec3 ambient  = prop.Ambient  * vec3(texture(Texture, OutUVCoords));
    vec3 diffuse  = prop.Diffuse  * diff * vec3(texture(Texture, OutUVCoords));
    vec3 specular = prop.Specular * spec * vec3(texture(Texture, OutUVCoords));
    return ambient + light.Intensity * light.Color * (diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, MaterialProperties prop, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.Position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), prop.Shininess);

    float distance    = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));    

    vec3 ambient  = prop.Ambient  * vec3(texture(Texture, OutUVCoords));
    vec3 diffuse  = prop.Diffuse  * diff * vec3(texture(Texture, OutUVCoords));
    vec3 specular = prop.Specular * spec * vec3(texture(Texture, OutUVCoords));
    return attenuation * light.Intensity * light.Color * (diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, MaterialProperties prop, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.Position - fragPos);
	
	float theta     = dot(lightDir, normalize(-light.Direction));
	float epsilon   = light.Cutoff - light.OuterCutoff;
	float intensity = clamp((theta - light.OuterCutoff) / epsilon, 0.0, 1.0);  
	
	float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), prop.Shininess);
	
	vec3 ambient  = prop.Ambient  * vec3(texture(Texture, OutUVCoords));
    vec3 diffuse  = prop.Diffuse  * diff * vec3(texture(Texture, OutUVCoords));
    vec3 specular = prop.Specular * spec * vec3(texture(Texture, OutUVCoords));
    return intensity * light.Intensity * light.Color * (diffuse + specular);
}

//Params
uniform MaterialProperties MatProp;
uniform DirectionalLight DirLight;
uniform PointLight PointLights[MAX_NO_POINT_LIGHTS];
uniform SpotLight Spot;

void main() {
	vec3 val = clamp(CalcDirLight(DirLight, MatProp, normalize(Normal), normalize(ViewPos - FragPos)), 0.0, 1.0);
	for(int i = 0; i < 4; i++)
		val += clamp(CalcPointLight(PointLights[i], MatProp, normalize(Normal), FragPos, normalize(ViewPos - FragPos)), 0.0, 1.0); 
	val += clamp(CalcSpotLight(Spot, MatProp, normalize(Normal), FragPos, normalize(ViewPos - FragPos)), 0.0, 1.0); 
	
    FragColor = MatProp.ObjectColor * vec4(clamp(val, 0.0, 1.0), 1.0);
}

