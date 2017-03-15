//
//  Scene.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "SceneObject.hpp"
#include "PhysicsWorld.hpp"
#include "../Scripting/Script.hpp"
#include "../Video/DepthMap.hpp"
#include "../Video/Camera.hpp"

namespace phoenix {
	namespace scene {
		class SceneManager;
		
		
		/** A scene handled by a scene manager */
		class Scene {
			friend class SceneManager;
			SceneManager *scene_manager;
			PhysicsWorld *physics_world;
			
			
			video::ShaderProgram *depth_shader;
			video::Camera *light_camera;
			video::DepthMap *depth_map;
			bool enable_shadows;
			
			
			std::vector<SceneObject*> objects;
			std::vector<scripting::MemberFunctionCallback> update_functions;
			std::vector<scripting::MemberFunctionCallback> render_functions;
			
			
			
			// Events
			void SceneMadeActive();
			void SceneMadeInactive();
			void Update(const UpdateInfo &info);
			void Render(const RenderInfo &info);
			void RenderScene(const RenderInfo &info);
			
			
			Scene(SceneManager *manager);
		public:
			~Scene();
			
			/** Sets the lighting camera */
			inline void SetLightCamera(video::Camera *camera) {
				light_camera = camera;
			}
			/** Returns the lighting camera */
			inline video::Camera* GetLightCamera() {
				return light_camera;
			}
			
			
			/** Returns the scene manager for this scene */
			inline SceneManager* GetSceneManager() const {
				return scene_manager;
			}
			/** Returns the physics world */
			inline PhysicsWorld* GetPhysicsWorld() {
				return physics_world;
			}
			
			/** Creates a new scene object */
			SceneObject* CreateSceneObject();
			
			/** Reserves some number of scene objects in memory */
			inline void ReserveSceneObjects(long count) {
				objects.reserve(count);
			}
			
			
			
			
			/** Adds a scripted update function */
			inline void AddUpdateFunction(scripting::MemberFunctionCallback function) {
				update_functions.push_back(function);
			}
			/** Adds a scripted render function */
			inline void AddRenderFunction(scripting::MemberFunctionCallback function) {
				render_functions.push_back(function);
			}
			
			
			
			static void Wrap(scripting::Script *script);
			
		};
		
		
	}
}

#endif /* Scene_hpp */
