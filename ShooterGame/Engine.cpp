//
//  Engine.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//


#include "Engine.hpp"
#include "Update.hpp"
#include "Util/Debug.hpp"

using namespace phoenix;



Engine* Engine::current = nullptr;
Engine::Engine(Platform *platform, gui::Display *display) : platform(platform), display(display) {
	
}
Engine::~Engine() {
	delete scene_manager;
	delete font_renderer;
	delete display;
}
Engine* Engine::New(Platform *platform) {
	if ( current == nullptr ) {
		gui::Display *display = gui::Display::New();
		
		// Check for an error
		if ( display == nullptr ) {
			LogError("Could not create engine: Could not initialize display");
			return nullptr;
		}
		else {
			// Make the display current and return the new Engine
			display->MakeCurrent();
			
			// Create a new engine
			current = new Engine(platform, display);
			current->Init();
			LogMessage("Sucessfully initialized Phoenix Engine %i.%i", current->version_major, current->version_minor);
			
			return current;
		}
	}
	else {
		LogError("Could not create engine: An engine is already created");
		return nullptr;
	}
}


void Engine::Init() {
	running = false;
	started = false;
	
	
	current_fps = 0;
	current_ups = 0;
	requested_fps = 0;
	requested_ups = 0;
	print_fps = true;
	print_ups = true;
	
	LogMessage("%s", platform->GetGameFolder().c_str());
	font_renderer = new video::FontRenderer();
	scene_manager = new scene::SceneManager(platform->GetGameFolder() + "/Scripts/main.lua");
}




void Engine::Start() {
	
	if ( !running ) {
		if ( game == nullptr ) {
			LogError("Game instance not set");
			exit(1);
		}
		else {
			// Start the game
			game->Start();
			
			// Start the scene manager
			scene_manager->Start();
			
		}
		
		
		// Start the update loop
		update_thread = new std::thread(Engine::UpdateLoopStarter, this);
		while ( !IsRunning() ) continue;
		
		// Start the render loop
		RenderLoop();
	}
	
}
void Engine::Stop() {
	if ( IsRunning() ) {
		game->Stop();
		
		LogMessage("Stopping engine");
		
		// Get the update thread to stop too
		running = false;
		update_thread->join();
		delete update_thread;
	}
	
}





void Engine::UpdateLoopStarter(void *engine) {
	((Engine*)engine)->UpdateLoop();
}
void Engine::UpdateLoop() {
	
	running = true;
	
	// Start the update timer
	Timer ups_timer;
	update_timer.Start();
	ups_timer.Start();
	
	double update_delta_time = 0;
	int update_count = 0;
	
	
	// Update loop
	while ( IsRunning() ) {
		
		// Create a new update info instance
		UpdateInfo info;
		info.engine = this;
		info.delta_time = update_timer.GetTime();
		
		
		
		// Check if an update is required
		if ( (update_delta_time = update_timer.GetTime().Seconds()) >= ((requested_ups <= 0) ? 0 : (1.0 / requested_ups)) ) {
			
			update_timer.Start();
			// Call the update callback
			scene_manager->Update(info);
			game->Update(info);
			
			++update_count;
		}
		
		
		// Check if it is time for a UPS print
		if ( ups_timer.GetTime().Seconds() >= 1.0 ) {
			current_ups = update_count;
			ups_timer.Start();
			
			// Print the ups
			if ( print_ups ) {
				LogMessage("UPS: %i", (int)update_count);
			}
			
			update_count = 0;
		}
		
	}
	
}
void Engine::RenderLoop() {
	
	
	
	// Start the render timer
	Timer render_timer, fps_timer;
	render_timer.Start();
	fps_timer.Start();
	
	
	double render_delta_time = 0;
	int frame_count = 0;
	
	
	
	
	
	// Render loop
	while ( IsRunning() ) {
		
		
		RenderInfo info;
		info.display = display;
		info.delta_time = render_timer.GetTime();
		
		
		// Check if an update is required
		if ( (render_delta_time = render_timer.GetTime().Seconds()) >= ((requested_fps <= 0) ? 0 : (1.0 / requested_fps)) ) {
			render_timer.Start();
			// Begin the render
			gui::Display *display = GetDisplay();
			display->BeginRender();
			
			// Render the stuff
			scene_manager->Render(info);
			game->Render(info);
			
			// Finish up the render
			display->FinishRender();
			display->PollEvents(this);
			
			++frame_count;
		}
		
		
		// Check if it is time for a UPS print
		if ( fps_timer.GetTime().Seconds() >= 1.0 ) {
			current_fps = frame_count;
			frame_count = 0;
			fps_timer.Start();
			
			// Print the fps
			if ( print_fps ) {
				LogMessage("FPS: %i", (int)current_fps);
			}
		}
	}
	
	
}











void Engine::Wrap(scripting::Script *script) {
	
	Duration::Wrap(script);
	UpdateInfo::Wrap(script);
	RenderInfo::Wrap(script);
	Platform::Wrap(script);
	gui::Display::Wrap(script);
	scene::SceneManager::Wrap(script);
	
	
	script->GetGlobalNamespace()
	.beginClass<Engine>("Engine")
	.addFunction("GetPlatform", &Engine::GetPlatform)
	.addFunction("GetDisplay", &Engine::GetDisplay)
	.addFunction("GetSceneManager", &Engine::GetSceneManager)
	.addFunction("IsRunning", &Engine::IsRunning)
	.addFunction("GetCurrentFPS", &Engine::GetCurrentFPS)
	.addFunction("GetCurrentUPS", &Engine::GetCurrentUPS)
	.addFunction("LockFPS", &Engine::LockFPS)
	.addFunction("LockUPS", &Engine::LockUPS)
	.addFunction("Stop", &Engine::Stop)
	.endClass();
	
	
}









