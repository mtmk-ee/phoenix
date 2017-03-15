//
//  Platform.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Platform.hpp"
#include "Scripting/Script.hpp"

using namespace phoenix;



Platform::Platform(int argc, char *argv[]) : argc(argc) {
	
	// Copy the argument information
	this->argv = new char*[argc + 1];
	for (int i = 0; i < argc + 1; ++i) {
		this->argv[i] = argv[i];
	}
	
	
}




void Platform::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<Platform>("Platform")
	.addFunction("SetGameFolder", &Platform::GetGameFolder)
	.addFunction("GetGameFolder", &Platform::GetGameFolder)
	.endClass();
	
	
}







