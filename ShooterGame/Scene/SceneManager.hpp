//
//  SceneManager.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include "Scene.hpp"
#include "PhysicsWorld.hpp"
#include "Audio/AudioManager.hpp"
#include <vector>

namespace phoenix {
	namespace scene {
		
		
		/** Manages scenes */
		class SceneManager {
			friend class Engine;
			
			std::string main_script_file;
			scripting::Script *main_script;
			audio::AudioManager *audio_manager;
			
			std::vector<Scene*> loaded_scenes;
			Scene *active_scene;
			
			
			
			
			
			
		public:
			SceneManager(const std::string &main_script);
			~SceneManager();
			
			
			/** Returns the main script */
			inline scripting::Script* GetMainScript() {
				return main_script;
			}
			/** Returns the audio manager */
			inline audio::AudioManager* GetAudioManager() {
				return audio_manager;
			}
			
			
			//Scene* LoadScene();
			/** Creates a new scene and adds it to this scene manager */
			Scene* CreateScene();
			/** Unloads the given scene and destroys it */
			void UnloadScene(Scene *scene);
			
			
			/** Sets the active scene */
			void SetActiveScene(Scene *scene);
			/** Returns the active scene */
			inline Scene* GetActiveScene() {
				return active_scene;
			}
			
			
			/** Starts the scene manager */
			void Start();
			/** Updates the scene manager */
			void Update(const UpdateInfo &info);
			/** Renders the scene manager */
			void Render(const RenderInfo &info);
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
	}
}

#endif /* SceneManager_hpp */
