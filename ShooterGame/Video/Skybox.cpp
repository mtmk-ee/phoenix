//
//  Skybox.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/10/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Skybox.hpp"
#include "Shader.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix::video;





Skybox::Skybox(CubemapTexture *texture, float size) : texture(texture) {
	LoadSkybox(size);
}
Skybox::~Skybox() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}



void Skybox::LoadSkybox(float size) {
	
	// Reserve some space for the vertices
	vertices.reserve(36);
	
	// Add vertices to the skybox
	// Neg-Z
	vertices.push_back(Vertex(FVec3(-size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size, -size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	
	// Neg-X
	vertices.push_back(Vertex(FVec3(-size, -size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size, -size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size, -size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	
	// Pos-X
	vertices.push_back(Vertex(FVec3(size, -size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	
	// Pos-Z
	vertices.push_back(Vertex(FVec3(-size, -size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size, -size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	
	// Pos-Y
	vertices.push_back(Vertex(FVec3(-size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size,  size), FVec3(0, 0, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size,  size, -size), FVec3(0, 0, 0), FVec2(0, 0)));
	
	// Neg-Y
	vertices.push_back(Vertex(FVec3(-size, -size, -size), FVec3(0, 1, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size, -size,  size), FVec3(0, 1, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size, -size), FVec3(0, 1, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size, -size), FVec3(0, 1, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(-size, -size,  size), FVec3(0, 1, 0), FVec2(0, 0)));
	vertices.push_back(Vertex(FVec3(size, -size,  size), FVec3(0, 1, 0), FVec2(0, 0)));
	
	// Create a new vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Generate a new buffer and upload the data to the GPU
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	// Enable vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
}

void Skybox::Render(phoenix::video::Camera *camera, ShaderProgram *program) {
	
	// Set shader uniforms
	program->UseProgram();
	program->SetUniformFMat4("projection", camera->GetProjectionMatrix());
	program->SetUniformFMat4("view", MatrixRemoveTranslation(camera->GetViewMatrix()));
	
	// Bind the cubemap texture
	texture->Bind();
	
	// Render the skybox
	glDepthMask(GL_FALSE);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}


void Skybox::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<Skybox>("Skybox")
	.addConstructor<void (*) (CubemapTexture*, float)>()
	.addFunction("Render", &Skybox::Render)
	.endClass();
}




