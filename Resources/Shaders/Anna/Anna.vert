#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec4 bone_weights;
layout (location = 4) in vec4 bone_ids;

out vec4 Vertex;
out vec4 Normal;
out vec2 UV;

const int BoneCount = 180;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 bones[BoneCount];


void main() {
	mat4 mvp = projection * view * model;
	
	mat4 bone_transform = bones[int(bone_ids[0])] * bone_weights[0];
	bone_transform     += bones[int(bone_ids[1])] * bone_weights[1];
	bone_transform     += bones[int(bone_ids[2])] * bone_weights[2];
	bone_transform     += bones[int(bone_ids[3])] * bone_weights[3];
	
	vec4 pos_l   = bone_transform * vec4(position, 1.0);
	gl_Position  = mvp * pos_l;
	
	vec4 normal_l = bone_transform * vec4(normal, 0.0);
	UV = uv;
	Normal = model * view * normal_l;
	Vertex = model * view * pos_l;
}
