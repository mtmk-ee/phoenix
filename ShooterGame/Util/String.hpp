//
//  String.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef String_hpp
#define String_hpp


#include <string>
#include <vector>
#include <sstream>
#include <map>




namespace phoenix {
	namespace scripting { class Script; }
	
	
	void WrapString(scripting::Script *script);
	
	
	
	/** Checks if two strings match */
	inline bool StringMatches(const std::string &str1, const std::string &str2) {
		return str1.compare(str2) == 0;
	}
	
	
	
	/** Trims the leading whitespace off a string */
	std::string StringTrimL(const std::string &str);
	/** Trims the trailing whitespace off a string */
	std::string StringTrimR(const std::string &str);
	/** Trims the whitespace off a string */
	inline std::string StringTrim(const std::string &str, bool left = true, bool right = true) {
		return StringTrimL(StringTrimR(str));
	}
	
	
	
	/** Returns the first character of a string */
	inline char StringFirstChar(const std::string &str) {
		return (str.length() == 0) ? '\0' : str[0];
	}
	/** Returns the last character of a string */
	inline char StringLastChar(const std::string &str) {
		return (str.length() == 0) ? '\0' : str[str.length() - 1];
	}
	/** Checks if a string starts with a given character */
	inline bool StringStartsWith(const std::string &str, char c) {
		return StringFirstChar(str) == c;
	}
	/** Checks if a string ends with a given character */
	inline bool StringEndsWith(const std::string &str, char c) {
		return StringLastChar(str) == c;
	}
	/** Checks if a string starts with another string */
	inline bool StringStartsWith(const std::string &str, const std::string &start) {
		const size_t strlen1 = str.length(), strlen2 = start.length();
		return ( (strlen2 > strlen1) || (strlen1 == 0) || (strlen2 == 0) ) ? false : (StringMatches(str.substr(0, strlen2), start));
	}
	/** Checks if a string ends with another string */
	inline bool StringEndsWith(const std::string &str, const std::string &end) {
		const size_t strlen1 = str.length(), strlen2 = end.length();
		return ( (strlen2 > strlen1) || (strlen1 == 0) || (strlen2 == 0) ) ? false : (StringMatches(str.substr(strlen1 - strlen2), end));
	}
	
	
	
	/** Splits a string by a single character */
	std::vector<std::string> StringSplitByChar(const std::string &str, const char delim);
	
	
	
	/** Converts an integral or float value to a string */
	template <typename T> inline std::string ToString(T t) {
		return std::to_string(t);
	}
	
	
	
	/** Converts a string to lower case */
	inline std::string StringToLowercase(const std::string &str) {
		std::string copy = str;
		std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
		return copy;
	}
	/** Converts a string to upper case */
	inline std::string StringToUppercase(const std::string &str) {
		std::string copy = str;
		std::transform(copy.begin(), copy.end(), copy.begin(), ::toupper);
		return copy;
	}
	
	
	
	/** Converts a string to an int */
	inline int StringToInt(const std::string &str) {
		int as_int = 0;
		
		std::stringstream sstream;
		sstream << str;
		sstream >> as_int;
		
		return as_int;
	}
	/** Converts a string to a float */
	inline float StringToFloat(const std::string &str) {
		float as_float = 0;
		
		std::stringstream sstream;
		sstream << str;
		sstream >> as_float;
		
		return as_float;
	}
	/** Converts a string to a bool */
	inline bool StringToBool(const std::string &str) {
		return StringMatches(StringTrim(StringToLowercase(str)), "true");
	}
	
	
	
	/** Replaces some text in a string */
	inline std::string StringReplace(const std::string &str, const std::string &find, const std::string &replace) {
		std::string copy = str;
		size_t find_loc;
		
		while ( (find_loc = copy.find(find)) != std::string::npos ) {
			copy = copy.replace(find_loc, find.length(), replace);
		}
		
		return copy;
	}
	
	
	
	/** Multi-replace */
	inline std::string StringMultiReplace(const std::string &str, const std::map<std::string, std::string> &find_replace) {
		std::string copy = str;
		size_t find_loc;
		
		// Loop through the characters
		for (auto it = find_replace.begin(); it != find_replace.end(); ++it) {
			size_t f_len = (*it).first.length();
			
			// Replace each character
			while ( (find_loc = copy.find((*it).first) != std::string::npos) ) {
				copy.replace(find_loc - 1, f_len, (*it).second);
			}
		}
		
		return copy;
	}
	
	
	
}

#endif /* String_hpp */
