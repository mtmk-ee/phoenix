//
//  Debug.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Debug_hpp
#define Debug_hpp

#include <iostream>

namespace phoenix {
	
	namespace scripting { class Script; }
	
	/** Returns a formatted time string */
	std::string GetFormattedTime(const std::string &format);
	
	
	
	
	
	/** Logs a message to the console */
	template <typename ...Args> inline void LogWithType(const std::string &type, const std::string &message, const Args&... args) {
		static bool locked = false;
		
		// To prevent threads from printing at the same time. Terrible for all threads performance-wise
		while ( locked ) continue;
		locked = true;
		
		
		printf("%s", type.c_str());
		printf("%s", GetFormattedTime("[%D %X]: ").c_str());
		printf(message.c_str(), args...);
		printf("\n");
		
		locked = false;
	}
	/** Logs a message to the console */
	template <typename ...Args> inline void LogMessage(const std::string &message, const Args&... args) {
		LogWithType("MESSAGE", message, args...);
	}
	/** Logs a warning to the console */
	template <typename ...Args> void LogWarning(const std::string &warning, const Args&... args) {
		LogWithType("WARNING", warning, args...);
	}
	/** Logs an error to the console */
	template <typename ...Args> void LogError  (const std::string &error, const Args&... args) {
		LogWithType("ERROR  ", error, args...);
	}
	
	
	
	
	
	
	
	void WrapDebug(scripting::Script *script);
	
	
	
}

#endif /* Debug_hpp */
