//
//  Platform.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Platform_hpp
#define Platform_hpp


#include "Util/Environment.hpp"


namespace phoenix {
	namespace scripting { class Script; }
	
	
	
	
	
	/** Platform information */
	class Platform {
		static Platform *platform;
		int argc;
		char **argv;
		
		
		std::string game_folder;
		
		
	public:
		Platform(int argc, char *argv[]);
		
		
		/** Sets the game folder for the platform */
		inline void SetGameFolder(const std::string &file) {
			game_folder = file;
		}
		/** Returns the game folder */
		inline std::string GetGameFolder() {
			return game_folder;
		}
		
		
		
		
		/** Returns the number of arguments supplied to the program */
		inline int GetArgCount() const {
			return argc;
		}
		/** Returns the argument list supplied to the program */
		inline char** GetArgVector() {
			return argv;
		}
		
		
		static void Wrap(scripting::Script *script);
		
		
	};
	
	
	
	
	
}

#endif /* Platform_hpp */
