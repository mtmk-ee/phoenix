//
//  VAO.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "VAO.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "../Scripting/Script.hpp"
#include "../Util/Debug.hpp"
#include <OpenGL/gl3.h>

using namespace phoenix::video;






VAO::~VAO() {
	Destroy();
}



bool VAO::Create() {
	if ( !created ) {
		
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		// Upload the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_data.size(), (GLfloat*)&vertex_data[0], GL_STATIC_DRAW);
		
		// Bind vertex attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLfloat*)0 + 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLfloat*)0 + 3);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (GLfloat*)0 + 5);
		
		
		// Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		
		return (created = true);
	}
	return false;
}
void VAO::Destroy() {
	vertex_data.clear();
	
	
	// Delete if already created
	if ( created ) {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		created = false;
	}
}



void VAO::Render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, (int)vertex_data.size());
	glBindVertexArray(0);
}




void VAO::Wrap(scripting::Script *script) {
	
	Vertex::Wrap(script);
	ShaderProgram::Wrap(script);
	Texture::Wrap(script);
	Camera::Wrap(script);
	Model::Wrap(script);
	
	script->GetGlobalNamespace()
	.beginClass<VAO>("VAO")
	.addStaticFunction("New", VAO::New)
	.addStaticFunction("Delete", VAO::Delete)
	.addFunction("AddVertex", &VAO::AddVertex)
	.addFunction("Create", &VAO::Create)
	.addFunction("IsCreated", &VAO::IsCreated)
	.addFunction("ReserveData", &VAO::ReserveData)
	.addFunction("Render", &VAO::Render)
	.endClass();
	
	
}







