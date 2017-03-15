//
//  Quaternion.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/7/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Quaternion.hpp"
#include "../Scripting/Script.hpp"



void phoenix::WrapQuaternion(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<Quaternion>("FQuat")
	.endClass()
	
	
	.beginNamespace("Quaternion")
	.addFunction("FromEuler", &QuaternionFromEuler)
	.addFunction("Normalize", &QuaternionNormalize)
	.endNamespace();
	;
	
	
}



