#version 330 core

out vec4 FragColor;
in vec2 OutUVCoords;

uniform vec3 LookDir;
uniform vec3 EyePos;
uniform vec2 PitchYaw;
uniform vec2 ScreenSize;

const int max_iterations = 512;
const float stop_threshold = 0.0001;
const float grad_step = 0.02;
const float clip_far = 1000.0;
const float PI = 3.14159265359;
const float DEG_TO_RAD = PI / 180.0;

float sdSphere(vec3 pos, float r) {
	return length(pos) - r;
}

float sdBox(vec3 p, vec3 b) {
	vec3 d = abs(p) - b;
	return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}

float primitive(vec3 pos) {
    float v = max(sdBox(pos, vec3(1.7)), sdSphere(pos, 2));

    return v;
}

float dist_field(vec3 pos) {
	mat4 tr = mat4(
		1.0, 0.0, 0.0, 8000.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
	
	vec4 translated = inverse(tr) * vec4(pos.xyz, 1.0);
	//return primitive(translated.xyz);
	return primitive(pos - vec3(8.0, 0.0, 0.0));
}

vec3 gradient(vec3 pos) {
	const vec3 dx = vec3( grad_step, 0.0, 0.0 );
	const vec3 dy = vec3( 0.0, grad_step, 0.0 );
	const vec3 dz = vec3( 0.0, 0.0, grad_step );
	return normalize (
		vec3(
			dist_field( pos + dx ) - dist_field( pos - dx ),
			dist_field( pos + dy ) - dist_field( pos - dy ),
			dist_field( pos + dz ) - dist_field( pos - dz )			
		)
	);
}

vec3 shading( vec3 v, vec3 n, vec3 eye ) {
	// ...add lights here...
	
	float shininess = 16.0;
	
	vec3 final = vec3( 0.0 );
	
	vec3 ev = normalize( v - eye );
	vec3 ref_ev = reflect( ev, n );
	
	// light 0
	{
		vec3 light_pos   = vec3( 20.0, 20.0, 20.0 );
		vec3 light_color = vec3( 1.0, 0.7, 0.7 );
	
		vec3 vl = normalize( light_pos - v );
	
		float diffuse  = max( 0.0, dot( vl, n ) );
		float specular = max( 0.0, dot( vl, ref_ev ) );
		specular = pow( specular, shininess );
		
		final += light_color * ( diffuse + specular ); 
	}
	
	// light 1
	{
		vec3 light_pos   = vec3( -20.0, -20.0, -20.0 );
		vec3 light_color = vec3( 0.3, 0.7, 1.0 );
	
		vec3 vl = normalize( light_pos - v );
	
		float diffuse  = max( 0.0, dot( vl, n ) );
		float specular = max( 0.0, dot( vl, ref_ev ) );
		specular = pow( specular, shininess );
		
		final += light_color * ( diffuse + specular ); 
	}

	//return vec3(0.0, 0.0, 1.0);
	return final;
}

bool ray_marching(vec3 eye, vec3 dir, inout float depth, inout vec3 n) {
	float currDepth = 0.0;
	for (int i = 0; i < max_iterations; i++) {
		vec3 pos = eye + currDepth * dir;
		float dist = dist_field(pos);
		if (dist < stop_threshold * i) {
			depth = currDepth;
			n = gradient(pos);
			return true;
		}

		currDepth += dist;
		if (currDepth >= depth) {
			n = vec3(1.0);
			return false;
		}
	}
	
	n = vec3(1.0);
	return false;
}

vec3 ray_dir(float fov, vec2 size, vec2 pos) {
	vec2 xy = pos - size * 0.5;

	float cot_half_fov = tan( ( 90.0 - fov * 0.5 ) * DEG_TO_RAD );	
	float z = size.y * 0.5 * cot_half_fov;
	
	return normalize( vec3( xy, z ) );
}

mat3 rotationXY(vec2 angle) {
	vec2 c = cos( angle );
	vec2 s = sin( angle );
	
	return mat3(
		c.y      ,  0.0, -s.y,
		s.y * s.x,  c.x,  c.y * s.x,
		s.y * c.x, -s.x,  c.y * c.x
	);
}


void main()
{ 
	vec3 forward = normalize(LookDir);
	vec3 right = normalize(cross(forward, vec3(0, 1, 0)));
    vec3 up = normalize(cross(right, forward));

	vec3 ro = EyePos;
	vec3 rd = normalize(forward * 1.67 + right * OutUVCoords.x * (ScreenSize.x / ScreenSize.y) + up * OutUVCoords.y);

	//vec3 dir = ray_dir(45.0, ScreenSize.xy, gl_FragCoord.xy);
	//vec3 eye = EyePos;

	//mat3 rot = rotationXY(PitchYaw);
	//dir = rot * dir;
	//eye = rot * eye;
	//dir = normalize(dir);
	
    float depth = 100.0;
    vec3 n = vec3( 0.0 );
	if (!ray_marching(ro, rd, depth, n)) {
		FragColor = vec4(0.0, 0.0, 0.0, 0.0);
        return;
	}
	
	vec3 pos = ro + rd * depth;
	FragColor = vec4(shading(pos, n, ro), 1.0);
}