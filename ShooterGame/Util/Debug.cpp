//
//  Debug.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Debug.hpp"
#include <ctime>
#include "../Scripting/Script.hpp"



std::string phoenix::GetFormattedTime(const std::string &format) {
	const int buffer_size = 512;
	
	
	// Find the local time
	time_t ctime;
	time(&ctime);
	
	// Create a buffer for the time string
	struct tm *time_info = localtime(&ctime);
	char buffer[buffer_size];
	
	// Format the string
	strftime(buffer, buffer_size, format.c_str(), time_info);
	
	return buffer;
}



void phoenix::WrapDebug(scripting::Script *script) {
	script->GetGlobalNamespace()
	.addFunction("LogMessage", LogMessage<>)
	.addFunction("LogWarning", LogWarning<>)
	.addFunction("LogError", LogError<>);
}


