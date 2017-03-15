#version 330

in vec4 Normal;
in vec4 Vertex;
in vec4 Vertex_MV;
in vec4 Normal_MV;
in vec2 UV;

uniform sampler2D color_map;
out vec4 frag_color;

uniform float ambient_intensity;
uniform float diffuse_intensity;
uniform float specular_intensity;

uniform vec3 light_pos;
uniform vec3 camera_pos;


void main() {
	vec4 light_color = vec4(1, 1, 1, 1);
	
	vec4 ambient = light_color * ambient_intensity;
	
	vec4 norm = normalize(Normal);
	vec4 light_dir = normalize(vec4(light_pos, 1) - Vertex);
	float diff = max(dot(norm, light_dir), 0);
	vec4 diffuse = diff * light_color * diffuse_intensity;
	
	norm = normalize(Normal_MV);
	float specular_intensity = 0.5;
	vec4 view_dir = normalize(vec4(camera_pos, 1) - Vertex);
	vec4 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0), 128);
	vec4 specular = specular_intensity * spec * light_color;
	
	
	
	vec4 result = vec4((ambient + diffuse + specular).xyz, 1) *  texture(color_map, UV);
	
    frag_color = result;
}
