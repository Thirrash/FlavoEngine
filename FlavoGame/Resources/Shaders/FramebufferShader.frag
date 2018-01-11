#version 330 core

out vec4 FragColor;
in vec2 OutUVCoords;

uniform sampler2D screenTexture;
uniform vec2 ScreenSize;
uniform vec2 MousePos;
uniform float lensToggle;

void main()
{ 
	const float lensSize = 0.1;
	
	vec2 p = OutUVCoords.xy;
    vec2 m = vec2(MousePos.x, ScreenSize.y - MousePos.y) / ScreenSize.xy;
    vec2 d = p - m;
    float r = sqrt(dot(d, d));

    vec2 uv;
    vec3 col = vec3(0.0, 0.0, 0.0);
    if (r > lensSize + 0.001 || lensToggle > 0.0) {
        uv = OutUVCoords;
        col = texture2D(screenTexture, uv).xyz;
    } else if (r < lensSize - 0.001) {
        // uv = m + vec2(d.x * abs(d.x), d.y * abs(d.y));
        uv = m + d * r; // a.k.a. m + normalize(d) * r * r
        // uv = m + normalize(d) * sin(r * 3.14159 * 0.5);
        // uv = m + normalize(d) * asin(r) / (3.14159 * 0.5);
        col = texture2D(screenTexture, vec2(uv.x, uv.y)).xyz;
    }
    FragColor = vec4(col, 1.0);
    //FragColor = texture(screenTexture, OutUVCoords);
}