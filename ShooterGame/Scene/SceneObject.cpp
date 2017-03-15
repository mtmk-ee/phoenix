//
//  SceneObject.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "SceneObject.hpp"
#include "SceneManager.hpp"

using namespace phoenix::scene;
using namespace phoenix::scripting;



SceneObject::SceneObject(Scene *scene) : scene(scene) {
	
}
SceneObject::~SceneObject() {
	
}




void SceneObject::Update(const phoenix::UpdateInfo &info) {
	// Call the update functions for the scene object
	std::lock_guard<std::mutex> lock(scene->GetSceneManager()->GetMainScript()->GetMutex());
	for (MemberFunctionCallback function : update_functions) {
		function.Call(info);
	}
}
void SceneObject::Render(const phoenix::RenderInfo &info) {
	// Call the render functions for the scene object
	std::lock_guard<std::mutex> lock(scene->GetSceneManager()->GetMainScript()->GetMutex());
	for (MemberFunctionCallback function : render_functions) {
		function.Call(info);
	}
}





void SceneObject::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<SceneObject>("SceneObject")
	.addFunction("AddUpdateFunction", &SceneObject::AddUpdateFunction)
	.addFunction("AddRenderFunction", &SceneObject::AddRenderFunction)
	.endClass();
	
}




