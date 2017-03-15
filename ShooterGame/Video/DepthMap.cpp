//
//  DepthMap.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "DepthMap.hpp"
#include "../Engine.hpp"

using namespace phoenix::video;




DepthMap::DepthMap(int width, int height) : width(width), height(height) {
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &depth_map);
	
	glBindTexture(GL_TEXTURE_2D, depth_map);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	
	// Set texture paramters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// Attach texture to framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthMap::UseFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}
void DepthMap::BindTexture() {
	glBindTexture(GL_TEXTURE_2D, depth_map);
}

void DepthMap::SetFramebufferViewport() {
	glViewport(0, 0, width, height);
}
void DepthMap::SetDisplayViewport() {
	IVec2 size = Engine::GetCurrent()->GetDisplay()->GetSize();
	glViewport(0, 0, size.x, size.y);
}








