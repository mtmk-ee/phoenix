//
//  Script.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Script.hpp"
#include "../Util/Debug.hpp"
#include "../Util/String.hpp"
#include "../Video/VAO.hpp"
#include "../Video/SkinnedMesh.hpp"
#include "../Video/FontRenderer.hpp"
#include "../Engine.hpp"
#include "../Util/Quaternion.hpp"
#include "../Scene/Audio/AudioManager.hpp"
#include "../Video/Skybox.hpp"


using namespace luabridge;
using namespace phoenix::scripting;


/** Sets the lua path used by the require(file) function to search for modules */
int SetLuaPath(lua_State* L, const char* path) {
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path");
	std::string cur_path = lua_tostring(L, -1);
	cur_path.append(";");
	cur_path.append(path);
	lua_pop(L, 1);
	lua_pushstring(L, cur_path.c_str());
	lua_setfield(L, -2, "path");
	lua_pop(L, 1);
	return 0;
}




Script::Script() {
	Init();
}
Script::Script(const std::string &file) {
	Init();
	EvalFile(file);
}
Script::~Script() {
	lua_close(state);
}


void Script::Init() {
	state = luaL_newstate();
	
	if ( state != NULL ) {
		
		// Open the lua libraries for the state
		luaL_openlibs(state);
		
		// Set the lua module search path
		SetLuaPath(state, (Engine::GetCurrent()->GetPlatform()->GetGameFolder() + "/?.lua").c_str());
		
		
		// Wrap the script class
		GetGlobalNamespace()
		.beginClass<Script>("Script")
		.addConstructor<void (*) ()>()
		.addFunction("EvalString", &Script::EvalString)
		.addFunction("EvalFile", &Script::EvalFile)
		.endClass()
		
		.addFunction("PrintOpenGLErrors", video::PrintOpenGLErrors);
		
		
		
		
		
		// Wrap the classes used by scripts
		Engine::Wrap(this);
		File::Wrap(this);
		scene::audio::AudioManager	::Wrap(this);
		video::VAO::Wrap(this);
		video::SkinnedMesh::Wrap(this);
		video::FontRenderer::Wrap(this);
		video::CubemapTexture::Wrap(this);
		video::Skybox::Wrap(this);
		MemberFunctionCallback::Wrap(this);
		WrapString(this);
		WrapDebug(this);
		WrapQuaternion(this);
		
		
		
		
		
		
		// Set globals
		Set("Engine", Engine::GetCurrent());
		Set("Display", Engine::GetCurrent()->GetDisplay());
		Set("Mouse", Engine::GetCurrent()->GetDisplay()->GetMouse());
		Set("Keyboard", Engine::GetCurrent()->GetDisplay()->GetKeyboard());
		Set("SceneManager", Engine::GetCurrent()->GetSceneManager());
		Set("FontRenderer", Engine::GetCurrent()->GetFontRenderer());
		Set("AudioManager", Engine::GetCurrent()->GetSceneManager()->GetAudioManager());
	}
}




bool Script::EvalFile(const std::string &file) {
	if ( luaL_loadfile(state, file.c_str()) || lua_pcall(state, 0, 0, 0) ) {
		LogError("Lua: %s", lua_tostring(state, -1));
		lua_pop(state, 1);  /* pop error message from the stack */
		return false;
	}
	return true;
}
bool Script::EvalString(const std::string &script) {
	int error = luaL_loadbuffer(state, script.c_str(), script.length(), "line") || lua_pcall(state, 0, 0, 0);
	if ( error ) {
		LogError("Lua: %s", lua_tostring(state, -1));
		lua_pop(state, 1);  /* pop error message from the stack */
		return false;
	}
	return true;
}





void MemberFunctionCallback::Wrap(phoenix::scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<MemberFunctionCallback>("MemberFunctionCallback")
	.addConstructor<void (*) (LuaRef, LuaRef)>()
	.endClass();
	
}







