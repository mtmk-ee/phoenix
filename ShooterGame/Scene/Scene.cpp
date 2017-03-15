//
//  Scene.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "../Engine.hpp"
#include "../Video/OpenGL.hpp"

using namespace phoenix::scene;
using namespace phoenix::video;
using namespace phoenix::scripting;





Scene::Scene(SceneManager *scene_manager) : scene_manager(scene_manager), enable_shadows(false), light_camera(nullptr) {
	physics_world = new PhysicsWorld();
	depth_map = new DepthMap(1024, 1024);
	
	// Load depth shader program
	std::string shader_folder = Engine::GetCurrent()->GetPlatform()->GetGameFolder() + "/Shaders/DepthShader";
	depth_shader = new ShaderProgram();
	ShaderSource *vert_shader = ShaderSource::Load(shader_folder + "/DepthShader.vert", 0);
	ShaderSource *frag_shader = ShaderSource::Load(shader_folder + "/DepthShader.frag", 1);
	depth_shader->AttachShader(vert_shader);
	depth_shader->AttachShader(frag_shader);
	depth_shader->LinkProgram();
	delete vert_shader;
	delete frag_shader;
}
Scene::~Scene() {
	
	// Destroy scene objects
	for (SceneObject *object : objects) {
		delete object;
	}
	objects.clear();
	
	// Delete the physics world
	delete physics_world;
	
	delete depth_shader;
}

SceneObject* Scene::CreateSceneObject() {
	// Create a new scene object and add it to the scene object vector
	SceneObject *object = new SceneObject(this);
	objects.push_back(object);
	return object;
}


void Scene::SceneMadeActive() {
	
}
void Scene::SceneMadeInactive() {
	
}



void Scene::RenderScene(const phoenix::RenderInfo &info) {
	// Render the scene into the framebuffer
	for (SceneObject *object : objects) {
		object->Render(info);
	}
	
	
	// Call the render callback functions
	std::lock_guard<std::mutex> lock(scene_manager->GetMainScript()->GetMutex());
	for (MemberFunctionCallback function : render_functions) {
		function.Call(info);
	}
}



void Scene::Update(const phoenix::UpdateInfo &info) {
	
	// Update the scene objects
	for (SceneObject *object : objects) {
		object->Update(info);
	}
	
	// Step the physics world
	physics_world->StepWorld(info.delta_time);
	
	// Call the update callback functions
	std::lock_guard<std::mutex> lock(scene_manager->GetMainScript()->GetMutex());
	for (MemberFunctionCallback function : update_functions) {
		function.Call(info);
	}
}
void Scene::Render(const phoenix::RenderInfo &info) {
	
	if ( enable_shadows && light_camera != nullptr ) {
		depth_map->SetFramebufferViewport();
		depth_map->UseFramebuffer();
		glClear(GL_DEPTH_BUFFER_BIT);
		depth_shader->UseProgram();
		depth_shader->SetUniformFMat4("lightspace_matrix", light_camera->GetProjectionMatrix() * light_camera->GetViewMatrix());
		
		
		RenderScene(info);
		
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		depth_map->SetDisplayViewport();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		depth_map->BindTexture();
		
		RenderScene(info);
	}
	else {
		RenderScene(info);
	}
}




void Scene::Wrap(scripting::Script *script) {
	
	SceneObject::Wrap(script);
	PhysicsWorld::Wrap(script);
	
	
	script->GetGlobalNamespace()
	.beginClass<Scene>("Scene")
	.addFunction("GetPhysicsWorld", &Scene::GetPhysicsWorld)
	.addFunction("CreateSceneObject", &Scene::CreateSceneObject)
	.addFunction("ReserveSceneObjects", &Scene::ReserveSceneObjects)
	.addFunction("GetSceneManager", &Scene::GetSceneManager)
	.addFunction("AddUpdateFunction", &Scene::AddUpdateFunction)
	.addFunction("AddRenderFunction", &Scene::AddRenderFunction)
	.endClass();
	
	
}




