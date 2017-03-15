//
//  Time.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Time.hpp"
#include "../Scripting/Script.hpp"
#include <chrono>

using namespace phoenix;



Duration Duration::Now() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


void Duration::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<Duration>("Duration")
	.addFunction("Seconds", &Duration::Seconds)
	.addFunction("Nanoseconds", &Duration::Nanoseconds)
	.addFunction("Milliseconds", &Duration::Milliseconds)
	.endClass();
}





