#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 position;


uniform mat4 model;
uniform mat4 lightspace_matrix;



void main() {
	gl_Position  = lightspace_matrix * model * vec4(position, 1.0);
}
