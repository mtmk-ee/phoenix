#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec4 bone_weights;
layout (location = 4) in vec4 bone_ids;

out vec4 Vertex;
out vec4 Normal;
out vec4 Vertex_MV;
out vec4 Normal_MV;
out vec2 UV;

const int BoneCount = 20;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 bones[BoneCount];


void main() {
	mat4 mvp = projection * view * model;
	mat4 bone_transform = mat4(1.0);
	
	vec4 pos_l   = bone_transform * vec4(position, 1.0);
	gl_Position  = mvp * pos_l;
	
	vec4 normal_l = bone_transform * vec4(normal, 0.0);
	UV = uv;
	Normal = model * normal_l;
	Vertex = model * pos_l;
	Vertex_MV = view * model * pos_l;
	Normal_MV = view * model * normal_l;
}
