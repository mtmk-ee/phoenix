//
//  Display.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Display.hpp"
#include "GLFW.hpp"
#include "../Util/Debug.hpp"
#include "../Util/Vector.hpp"
#include "../Util/Matrix.hpp"
#include "../Engine.hpp"

using namespace phoenix;
using namespace phoenix::gui;



Display::Display(void *window) : window(window), keyboard(this), mouse(this) {
	
}
Display::~Display() {
	glfwDestroyWindow((GLFWwindow*)window);
}

Display* Display::New() {
	GLFW::Init();
	
	// Window creation hints
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 8);
	
	// Create the window
	GLFWwindow *window = glfwCreateWindow(800, 500, "Phoenix Game Engine", nullptr, nullptr);
	
	
	// Error
	if ( window == nullptr ) {
		LogError("Could not create GLFW window");
		return nullptr;
	}
	// Success
	else {
		LogMessage("Successfully created GLFW window");
		
		glfwMakeContextCurrent((GLFWwindow*)window);
		
		glClearColor(1, 1, 1, 1);
		
		
		// Depth testing
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		
		// Face culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		
		// Enable 2D textures
		glEnable(GL_TEXTURE_2D);
		
		
		
		// Return the window
		return new Display(window);
	}
}


void Display::CaptureMouse(bool captured) {
	glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}


void Display::SetClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
void Display::Maximize() {
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SetLocation(IVec2(0, 0));
	SetSize(IVec2(mode->width, mode->height));
}
void Display::MakeCurrent() {
	glfwMakeContextCurrent((GLFWwindow*)window);
}


void Display::SetTitle(const std::string &name) {
	glfwSetWindowTitle((GLFWwindow*)window, name.c_str());
}
void Display::SetLocation(const IVec2 &location) {
	glfwSetWindowPos((GLFWwindow*)window, location.x, location.y);
}
void Display::SetSize(const IVec2 &size) {
	glfwSetWindowSize((GLFWwindow*)window, size.x, size.y);
}
IVec2 Display::GetSize() {
	int w, h;
	glfwGetWindowSize((GLFWwindow*)window, &w, &h);
	return IVec2(w, h);
}
IVec2 Display::GetLocation() {
	int x, y;
	glfwGetWindowPos((GLFWwindow*)window, &x, &y);
	return IVec2(x, y);
}



void Display::BeginRender() {
	MakeCurrent();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Display::FinishRender() {
	glfwSwapBuffers((GLFWwindow*)window);
}
void Display::PollEvents(Engine *engine) {
	glfwPollEvents();
	mouse.Update();
	
	if ( glfwWindowShouldClose((GLFWwindow*)window) ) {
		engine->Stop();
	}
}






void Display::Wrap(scripting::Script *script) {
	
	WrapVectors(script);
	WrapMatrices(script);
	
	Mouse::Wrap(script);
	Keyboard::Wrap(script);
	
	
	script->GetGlobalNamespace()
	.beginClass<Display>("Display")
	.addFunction("SetClearColor", &Display::SetClearColor)
	.addFunction("CaptureMouse", &Display::CaptureMouse)
	.addFunction("SetTitle", &Display::SetTitle)
	.addFunction("GetSize", &Display::GetSize)
	.addFunction("GetLocation", &Display::GetLocation)
	.addFunction("SetSize", &Display::SetSize)
	.addFunction("SetLocation", &Display::SetLocation)
	.addFunction("Maximize", &Display::Maximize)
	.addFunction("GetMouse", &Display::GetMouse)
	.addFunction("GetKeyboard", &Display::GetKeyboard)
	.endClass();
	
}




