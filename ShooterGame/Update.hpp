//
//  Update.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Update_hpp
#define Update_hpp

#include "Util/Time.hpp"


namespace phoenix {
	class Engine;
	namespace gui { class Display; }
	namespace scripting { class Script; }
	
	/** Information about an engine update */
	struct UpdateInfo {
		Engine *engine;
		Duration delta_time;
		
		static void Wrap(scripting::Script *script);
	};
	
	/** Information about an engine render */
	struct RenderInfo {
		gui::Display *display;
		Duration delta_time;
		
		static void Wrap(scripting::Script *script);
	};
	
	
	
	
}

#endif /* Update_hpp */
