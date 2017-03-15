//
//  Texture.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Texture.hpp"
#include "../Util/Debug.hpp"
#include "../Scripting/Script.hpp"

#include <OpenGL/gl3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace phoenix::video;




Texture::~Texture() {
	glDeleteTextures(1, &tex_id);
	tex_id = 0;
}


Texture *Texture::Load(GLenum target, const std::string &file) {
	unsigned char *image;
	
	// Load the image with STBI
	int width, height, comp;
	image = stbi_load(file.c_str(), &width, &height, &comp, STBI_rgb_alpha);
	
	
	if ( image == nullptr ) {
		LogError("Could not load file \"%s\"", file.c_str());
		return nullptr;
	}
	else {
		glEnable(target);
		
		// Generate and bind texture
		GLuint tex_id;
		glGenTextures(1, &tex_id);
		glBindTexture(target, tex_id);
		
		// Upload texture
		glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		// Set texture parameters
		glGenerateMipmap(target);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, 3);
		
		// Finish up
		glBindTexture(target, 0);
		stbi_image_free(image);
		
		return new Texture(target, tex_id, width, height, file);
	}
}


void Texture::Bind(GLenum tex_unit) {
	glActiveTexture(tex_unit);
	glBindTexture(target, tex_id);
}
void Texture::Unbind() {
	glBindTexture(target, 0);
}



void Texture::Wrap(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<Texture>("Texture")
	.addStaticFunction("Load", Texture::Load)
	.addFunction("GetWidth", &Texture::GetWidth)
	.addFunction("GetHeight", &Texture::GetHeight)
	.addFunction("Bind", &Texture::Bind)
	.endClass();
	
}



