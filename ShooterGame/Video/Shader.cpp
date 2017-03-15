//
//  Shader.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/12/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Shader.hpp"
#include "../Util/Debug.hpp"
#include "../Util/File.hpp"
#include "../Scripting/Script.hpp"
#include "OpenGL.hpp"
#include <iostream>


using namespace phoenix;
using namespace phoenix::video;
using namespace std;








inline GLuint GetGLShaderType(ShaderType type) {
	switch ( type ) {
		case PHOENIX_SHADER_VERTEX:
			return GL_VERTEX_SHADER;
		case PHOENIX_SHADER_FRAGMENT:
			return GL_FRAGMENT_SHADER;
		default:
			return 0;
	}
}



ShaderSource::~ShaderSource() {
	glDeleteShader(GetID());
}
ShaderSource* ShaderSource::Load(const std::string &file, int shader_type) {
	return ShaderSource::New(File(file).ReadText(), shader_type);
}
ShaderSource* ShaderSource::New(const std::string &source, int shader_type) {
	GLuint shader = glCreateShader(GetGLShaderType((ShaderType)shader_type));
	
	// Load and compile the shader
	const char *vert_source_c = source.c_str();
	glShaderSource(shader, 1, &vert_source_c, NULL);
	glCompileShader(shader);
	
	// Check if the compilation was successful
	GLint success;
	GLchar info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if ( !success ) {
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		LogError("Shader Compilation error: %s", info_log);
		return nullptr;
	}
	else {
		return new ShaderSource(shader);
	}
}



void ShaderSource::Wrap(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<ShaderSource>("ShaderSource")
	.addStaticFunction("Load", ShaderSource::Load)
	.addStaticFunction("Delete", ShaderSource::Delete)
	.endClass();
	
}







ShaderProgram::ShaderProgram() : created(false) {
	program_id = glCreateProgram();
}
ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program_id);
}

void ShaderProgram::AttachShader(ShaderSource *source) {
	if ( source != nullptr ) glAttachShader(program_id, source->GetID());
	else LogError("Attempted to attach null shader");
}
bool ShaderProgram::LinkProgram() {
	if ( !IsLinked() ) {
		
		// Link the program
		glLinkProgram(program_id);
		
		// Check if the link was successful
		GLint success;
		GLchar info_log[512];
		glGetProgramiv(program_id, GL_LINK_STATUS, &success);
		if ( !success ) {
			glGetProgramInfoLog(program_id, 512, NULL, info_log);
			LogError("Shader Program linker error: %s", info_log);
			return false;
		}
		else {
			return (created = true);
		}
	}
	else return true;
}
void ShaderProgram::UseProgram() {
	if ( IsLinked() )
		glUseProgram(program_id);
}
void ShaderProgram::UnbindProgram() {
	glUseProgram(0);
}



void ShaderProgram::Wrap(scripting::Script *script) {
	
	ShaderSource::Wrap(script);
	
	script->GetGlobalNamespace()
	.beginClass<ShaderProgram>("ShaderProgram")
	.addConstructor<void (*) ()>()
	.addStaticFunction("New", ShaderProgram::New)
	.addFunction("IsLinked", &ShaderProgram::IsLinked)
	.addFunction("AttachShader", &ShaderProgram::AttachShader)
	.addFunction("LinkProgram", &ShaderProgram::LinkProgram)
	.addFunction("UseProgram", &ShaderProgram::UseProgram)
	.addFunction("UnbindProgram", &ShaderProgram::UnbindProgram)
	.addFunction("SetModelMatrix", &ShaderProgram::SetModelMatrix)
	.addFunction("SetViewMatrix", &ShaderProgram::SetViewMatrix)
	.addFunction("SetMVPMatrix", &ShaderProgram::SetMVPMatrix)
	.addFunction("SetCameraPositiion", &ShaderProgram::SetCameraPosition)
	.addFunction("SetUniformFloat", &ShaderProgram::SetUniformFloat)
	.addFunction("SetUniformFVec2", &ShaderProgram::SetUniformFVec2)
	.addFunction("SetUniformFVec3", &ShaderProgram::SetUniformFVec3)
	.addFunction("SetUniformFVec4", &ShaderProgram::SetUniformFVec4)
	.addFunction("SetUniformFMat3", &ShaderProgram::SetUniformFMat3)
	.addFunction("SetUniformFMat4", &ShaderProgram::SetUniformFMat4)
	.addFunction("SetUniformInt", &ShaderProgram::SetUniformInt)
	.endClass();
	
}







/* Set uniforms */
void ShaderProgram::SetUniform(const string &name, float* values, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform1fv(loc, count, values);
}
void ShaderProgram::SetUniformFloat(const string &name, const float value) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform1fv(loc, 1, &value);
}
void ShaderProgram::SetUniform(const string &name, glm::vec2* vectors, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform2fv(loc, count, (GLfloat*)vectors);
}
void ShaderProgram::SetUniformFVec2(const string &name, const glm::vec2 &vector) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform2fv(loc, 1, (GLfloat*)&vector);
}
void ShaderProgram::SetUniform(const string &name, glm::vec3* vectors, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform3fv(loc, count, (GLfloat*)vectors);
}
void ShaderProgram::SetUniformFVec3(const string &name, const glm::vec3 &vector) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform3fv(loc, 1, (GLfloat*)&vector);
}
void ShaderProgram::SetUniform(const string &name, glm::vec4* vectors, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform4fv(loc, count, (GLfloat*)vectors);
}
void ShaderProgram::SetUniformFVec4(const string &name, const glm::vec4 &vector) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform4fv(loc, 1, (GLfloat*)&vector);
}
void ShaderProgram::SetUniform(const string &name, glm::mat3* matrices, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniformMatrix3fv(loc, count, false, (GLfloat*)matrices);
}
void ShaderProgram::SetUniformFMat3(const string &name, const glm::mat3 &matrix) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniformMatrix3fv(loc, 1, false, (GLfloat*)&matrix);
}
void ShaderProgram::SetUniform(const string &name, glm::mat4* matrices, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	if ( loc != -1 ) glUniformMatrix4fv(loc, count, false, (GLfloat*)matrices);
}
void ShaderProgram::SetUniformFMat4(const string &name, const glm::mat4 &matrix) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	if ( loc != -1 ) glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat*)&matrix);
}
void ShaderProgram::SetUniform(const string &name, int* values, int count) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform1iv(loc, count, values);
}
void ShaderProgram::SetUniformInt(const string &name, const int value) {
	int loc = glGetUniformLocation(program_id, name.c_str());
	glUniform1i(loc, value);
}









