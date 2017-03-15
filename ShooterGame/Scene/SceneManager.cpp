//
//  SceneManager.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "SceneManager.hpp"

using namespace phoenix::scene;



SceneManager::SceneManager(const std::string &main_script) : active_scene(nullptr), main_script_file(main_script) {
	audio_manager = new audio::AudioManager();
}
SceneManager::~SceneManager() {
	// Delete the loaded scenes
	for (Scene *scene : loaded_scenes) {
		delete scene;
	}
	
	// Delete the audio manager
	delete audio_manager;
}


Scene* SceneManager::CreateScene() {
	
	// Create a new scene and add it to the scene vector
	Scene *scene = new Scene(this);
	loaded_scenes.push_back(scene);
	
	return scene;
}
void SceneManager::UnloadScene(phoenix::scene::Scene *scene) {
	
	// Find the given scene
	auto it = std::find(loaded_scenes.begin(), loaded_scenes.end(), scene);
	
	
	if ( it != loaded_scenes.end() ) {
		// Remove the scene from the list
		loaded_scenes.erase(it);
		
		// Delete the scene
		delete *it;
	}
}


void SceneManager::SetActiveScene(phoenix::scene::Scene *scene) {
	
	// Make sure the scene belongs to this scene manager
	if ( scene->scene_manager == this ) {
		Scene *old_active_scene = active_scene;
		active_scene = scene;
		
		// Call scene events
		if ( old_active_scene != nullptr )
			old_active_scene->SceneMadeInactive();
		if ( active_scene != nullptr )
			active_scene->SceneMadeActive();
	}
}


void SceneManager::Start() {
	// Create a new script
	main_script = new scripting::Script();
	
	// Lock the script mutex and evaluate the main script file
	std::lock_guard<std::mutex> lock(main_script->GetMutex());
	main_script->EvalFile(main_script_file);
}
void SceneManager::Update(const phoenix::UpdateInfo &info) {
	
	// Update the scene
	if ( active_scene != nullptr ) {
		active_scene->Update(info);
	}
	
	// Lock the main script and call the update function
	std::lock_guard<std::mutex> lock(main_script->GetMutex());
	luabridge::LuaRef update_func = main_script->Get("Update");
	if ( !update_func.isNil() && update_func.isFunction() ) {
		update_func(info);
	}
	
}
void SceneManager::Render(const phoenix::RenderInfo &info) {
	
	// Render the scene
	if ( active_scene != nullptr ) {
		active_scene->Render(info);
	}
	
	// Lock the main script and call the render function
	std::lock_guard<std::mutex> lock(main_script->GetMutex());
	luabridge::LuaRef render_func = main_script->Get("Render");
	if ( !render_func.isNil() && render_func.isFunction() ) {
		render_func(info);
	}
	
}



void SceneManager::Wrap(scripting::Script *script) {
	Scene::Wrap(script);
	
	script->GetGlobalNamespace()
	.beginClass<SceneManager>("SceneManager")
	.addFunction("CreateScene", &SceneManager::CreateScene)
	.addFunction("UnloadScene", &SceneManager::UnloadScene)
	.addFunction("SetActiveScene", &SceneManager::SetActiveScene)
	.addFunction("GetActiveScene", &SceneManager::GetActiveScene)
	.endClass();
	
	
}








