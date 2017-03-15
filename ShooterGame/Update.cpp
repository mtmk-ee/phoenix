//
//  Update.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Update.hpp"
#include "Scripting/Script.hpp"

using namespace phoenix;




void UpdateInfo::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<UpdateInfo>("UpdateInfo")
	.addData("engine", &UpdateInfo::engine)
	.addData("delta_time", &UpdateInfo::delta_time)
	.endClass();
}
void RenderInfo::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<RenderInfo>("RenderInfo")
	.addData("display", &RenderInfo::display)
	.addData("delta_time", &RenderInfo::delta_time)
	.endClass();
}






