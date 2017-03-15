//
//  CubemapTexture.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/10/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "CubemapTexture.hpp"
#include "../Util/Debug.hpp"
#include "../Scripting/Script.hpp"
#include <stb/stb_image.h>

using namespace phoenix::video;


struct CubemapTextureSide {
	unsigned char *image;
	int width, height, comp;
};


void CubemapTextureInfo::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<CubemapTextureInfo>("CubemapTextureInfo")
	.addConstructor<void (*) ()>()
	.addData("posx_path", &CubemapTextureInfo::posx_path)
	.addData("negx_path", &CubemapTextureInfo::negx_path)
	.addData("posy_path", &CubemapTextureInfo::posy_path)
	.addData("negy_path", &CubemapTextureInfo::negy_path)
	.addData("posz_path", &CubemapTextureInfo::posz_path)
	.addData("negz_path", &CubemapTextureInfo::negz_path)
	.endClass();
}


CubemapTexture* CubemapTexture::Load(const CubemapTextureInfo &texture_info) {
	CubemapTextureSide posx, negx, posy, negy, posz, negz;
	
	// Load images
	posx.image = stbi_load(texture_info.posx_path.c_str(), &posx.width, &posx.height, &posx.comp, STBI_rgb_alpha);
	negx.image = stbi_load(texture_info.negx_path.c_str(), &negx.width, &negx.height, &negx.comp, STBI_rgb_alpha);
	posy.image = stbi_load(texture_info.posy_path.c_str(), &posy.width, &posy.height, &posy.comp, STBI_rgb_alpha);
	negy.image = stbi_load(texture_info.negy_path.c_str(), &negy.width, &negy.height, &negy.comp, STBI_rgb_alpha);
	posz.image = stbi_load(texture_info.posz_path.c_str(), &posz.width, &posz.height, &posz.comp, STBI_rgb_alpha);
	negz.image = stbi_load(texture_info.negz_path.c_str(), &negz.width, &negz.height, &negz.comp, STBI_rgb_alpha);
	
	if ( posx.image == nullptr || negx.image == nullptr || posy.image == nullptr || negy.image == nullptr || posz.image == nullptr || negz.image == nullptr ) {
		LogError("Could not load cubemap texture");
		stbi_image_free(posx.image);
		stbi_image_free(negx.image);
		stbi_image_free(posy.image);
		stbi_image_free(negy.image);
		stbi_image_free(posz.image);
		stbi_image_free(negz.image);
		
		return nullptr;
	}
	else {
		
		// Create OpenGL textures
		GLuint tex_id;
		glGenTextures(1, &tex_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);
		
		// Upload textures to GPU
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, posx.width, posx.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, posx.image);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, negx.width, negx.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, negx.image);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, posy.width, posy.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, posy.image);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, negy.width, negy.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, negy.image);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, posz.width, posz.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, posz.image);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, negz.width, negz.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, negz.image);
		
		// Set up texture paramters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		
		// Free the images
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		stbi_image_free(posx.image);
		stbi_image_free(negx.image);
		stbi_image_free(posy.image);
		stbi_image_free(negy.image);
		stbi_image_free(posz.image);
		stbi_image_free(negz.image);
		
		return new CubemapTexture(tex_id);
	}
}
CubemapTexture::~CubemapTexture() {
	glDeleteTextures(1, &tex_id);
	tex_id = 0;
}



void CubemapTexture::Bind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);
}



void CubemapTexture::Wrap(scripting::Script *script) {
	CubemapTextureInfo::Wrap(script);
	
	script->GetGlobalNamespace()
	.beginClass<CubemapTexture>("CubemapTexture")
	.addStaticFunction("Load", CubemapTexture::Load)
	.addFunction("Bind", &CubemapTexture::Bind)
	.endClass();
}









