//
//  Engine.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include "Game.hpp"
#include "Platform.hpp"
#include "Util/Time.hpp"
#include "GUI/Display.hpp"
#include "Scene/SceneManager.hpp"
#include "Video/FontRenderer.hpp"
#include <thread>

namespace phoenix {
	
	
	
	
	class Engine {
		static Engine *current;
		Platform *platform;
		int version_major = 0;
		int version_minor = 1;
		
		
		// Engine state
		bool running, started;
		
		// UPS / FPS
		int current_ups, current_fps;
		int requested_ups, requested_fps;
		bool print_fps, print_ups;
		
		
		// Update / Render
		std::thread *update_thread;
		Timer update_timer;
		
		
		// Engine components
		phoenix::Game *game;
		gui::Display *display;
		video::FontRenderer *font_renderer;
		scene::SceneManager *scene_manager;
		
		
		// Private constructor
		Engine(Platform *platform, gui::Display *display);
		~Engine();
		
		
		void Init();
		
		// Loop functions
		static void UpdateLoopStarter(void *engine);
		void UpdateLoop();
		void RenderLoop();
		
		
		Engine(Engine &other) = delete;
		Engine(const Engine &other) = delete;
		
		
	public:
		/** Creates a new engine instance */
		static Engine* New(Platform *platform);
		/** Deletes an engine instance */
		static inline void Delete(Engine *engine) {
			if ( engine != nullptr ) {
				engine->Stop();
				
				delete engine;
				current = nullptr;
			}
		}
		
		
		
		/** Returns the current engine */
		inline static Engine* GetCurrent() {
			return current;
		}
		/** Returns the platform for this engine */
		inline Platform* GetPlatform() {
			return platform;
		}
		/** Returns the display */
		inline gui::Display* GetDisplay() {
			return display;
		}
		/** Returns the font renderer */
		inline video::FontRenderer* GetFontRenderer() {
			return font_renderer;
		}
		/** Returns the scene manager */
		inline scene::SceneManager* GetSceneManager() {
			return scene_manager;
		}
		/** Sets the game class */
		inline void SetGame(Game *game) {
			this->game = game;
		}
		/** Returns the game class */
		inline Game* GetGame() {
			return game;
		}
		
		
		
		
		
		/** Checks if the engine is running */
		inline bool IsRunning() const {
			return running;
		}
		
		
		
		/** Returns the current UPS of the engine */
		inline int GetCurrentUPS() const {
			return current_ups;
		}
		/** Returns the current FPS of the engine */
		inline int GetCurrentFPS() const  {
			return current_fps;
		}
		/** Locks the framerate. Use a value <= 0 for no lock */
		inline void LockFPS(int fps) {
			requested_fps = fps;
		}
		/** Locks the update rate. Use a value <= 0 for no lock */
		inline void LockUPS(int ups) {
			requested_ups = ups;
		}
		
		/** Returns the time since the last update */
		inline double GetDeltaTime() const {
			return update_timer.GetTime().Seconds();
		}
		
		
		static void Wrap(scripting::Script *script);
		
		
		
		/** Starts the engine. Call this method only once */
		void Start();
		/** Stops the engine */
		void Stop();
	};
	
	
	
	
}

#endif /* Engine_hpp */
