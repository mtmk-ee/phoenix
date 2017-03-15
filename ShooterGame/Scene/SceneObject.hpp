//
//  SceneObject.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include "../Scripting/Script.hpp"
#include "../Update.hpp"
#include <vector>


namespace phoenix {
	namespace scripting { class Script; }
	
	
	namespace scene {
		class Scene;
		
		
		/** An object in a scene */
		class SceneObject {
			friend class Scene;
			Scene *scene;
			
			
			std::vector<scripting::MemberFunctionCallback> update_functions;
			std::vector<scripting::MemberFunctionCallback> render_functions;
			
		public:
			SceneObject(Scene *scene);
			~SceneObject();
			
			/** Adds a scripted update function */
			inline void AddUpdateFunction(scripting::MemberFunctionCallback function) {
				update_functions.push_back(function);
			}
			/** Adds a scripted render function */
			inline void AddRenderFunction(scripting::MemberFunctionCallback function) {
				render_functions.push_back(function);
			}
			
			/** Updates the scene object */
			void Update(const UpdateInfo &info);
			/** Renders the scene object */
			void Render(const RenderInfo &info);
			
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
	}
}

#endif /* SceneObject_hpp */
