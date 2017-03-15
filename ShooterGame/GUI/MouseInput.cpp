//
//  MouseInput.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "MouseInput.hpp"
#include "Display.hpp"
#include "../Scripting/Script.hpp"
#include <GLFW/glfw3.h>

using namespace phoenix::gui;


bool Mouse::IsButtonPressed(int button) {
	return glfwGetMouseButton((GLFWwindow*)display->GetWindowHandle(), button);
}

void Mouse::Update() {
	old_x = x;
	old_y = y;
	
	// Update the stored mouse position
	glfwGetCursorPos((GLFWwindow*)display->GetWindowHandle(), &x, &y);
	
	// If it's the first update, the old mouse position must equal the new mouse position
	if ( first_update ) {
		old_x = x;
		old_y = y;
		first_update = false;
	}
}




void Mouse::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<Mouse>("Mouse")
	.addFunction("GetDeltaX", &Mouse::GetDeltaX)
	.addFunction("GetDeltaY", &Mouse::GetDeltaY)
	.addFunction("GetX", &Mouse::GetX)
	.addFunction("GetY", &Mouse::GetY)
	.addFunction("IsButtonPressed", &Mouse::IsButtonPressed)
	.endClass();
	
	
}







