//
//  GLFW.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "GLFW.hpp"
#include "../Util/Debug.hpp"

using namespace phoenix::gui;





void GLFW_Error(int code, const char *msg) {
	phoenix::LogError("Could not initialize GLFW: %s", msg);
}



GLFW GLFW::instance = GLFW();
GLFW::GLFW() : init(false) {
	
}
GLFW::~GLFW() {
	glfwTerminate();
}


void GLFW::Init() {
	if ( !IsInit() ) {
		glfwSetErrorCallback(GLFW_Error);
		
		// Initialize GLFW
		if ( !glfwInit() ) exit(1);
		else {
			// GLFW was successfully initialized
			int major, minor, revision;
			glfwGetVersion(&major, &minor, &revision);
			LogMessage("Successfully initialized GLFW %i.%i.%i", major, minor, revision);
			
			// Set the initialization flag to true
			instance.init = true;
		}
	}
}
