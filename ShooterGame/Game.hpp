//
//  Game.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/19/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Update.hpp"


namespace phoenix {
	namespace scripting { class Script; }
	
	
	class Game {
	protected:
		scripting::Script *main_script;
		
	public:
		inline Game(scripting::Script *main_script) : main_script(main_script) {
			
		}
		inline virtual ~Game() {
			
		}
		
		
		inline scripting::Script* GetMainScript() {
			return main_script;
		}
		
		
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual void Update(const UpdateInfo &info) = 0;
		virtual void Render(const RenderInfo &info) = 0;
	};
	
	
}

#endif /* Game_hpp */
