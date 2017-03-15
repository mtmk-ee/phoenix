//
//  String.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "String.hpp"
#include "../Scripting/Script.hpp"
#include <functional>



void phoenix::WrapString(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginNamespace("String")
	.addFunction("TrimL", StringTrimL)
	.addFunction("TrimR", StringTrimR)
	.addFunction("Trim", StringTrim)
	.addFunction("ToLowercase", StringToLowercase)
	.addFunction("ToUppercase", StringToUppercase)
	.addFunction("Replace", StringReplace)
	.endNamespace();
	
	
}





/* Trim Functions */
std::string phoenix::StringTrimL(const std::string &in_str) {
	std::string str = in_str;
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return str;
}
std::string phoenix::StringTrimR(const std::string &in_str) {
	std::string str = in_str;
	str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
	return str;
}




/* Split Functions */
std::vector<std::string> phoenix::StringSplitByChar(const std::string &str, const char delim) {
	std::stringstream test(str);
	std::string segment;
	std::vector<std::string> seglist;
	
	while(std::getline(test, segment, delim))
	{
		seglist.push_back(segment);
	}
	return seglist;
}
