//
//  DebugDrawer.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/6/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "DebugDrawer.hpp"
#include "../Engine.hpp"

using namespace phoenix::scene;
using namespace phoenix::video;





DebugDrawer::DebugDrawer() {
	program = new ShaderProgram();
	ShaderSource *vert = ShaderSource::Load(Engine::GetCurrent()->GetPlatform()->GetGameFolder() + "/Shaders/Lines.vert", 0);
	ShaderSource *frag = ShaderSource::Load(Engine::GetCurrent()->GetPlatform()->GetGameFolder() + "/Shaders/Lines.frag", 1);
	program->AttachShader(vert);
	program->AttachShader(frag);
	program->LinkProgram();
	
	delete vert;
	delete frag;
}












