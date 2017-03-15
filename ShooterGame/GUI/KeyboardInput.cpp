//
//  KeyboardInput.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "KeyboardInput.hpp"
#include "Display.hpp"
#include "../Util/String.hpp"
#include "../Scripting/Script.hpp"
#include <GLFW/glfw3.h>

using namespace phoenix;
using namespace phoenix::gui;




Keyboard::Keyboard(Display *display) : display(display) {
	
}


bool Keyboard::IsKeyPressed(Key key) {
	return glfwGetKey((GLFWwindow*)display->GetWindowHandle(), (int)key);
}
bool Keyboard::IsKeyCharPressed(char key) {
	return glfwGetKey((GLFWwindow*)display->GetWindowHandle(), CharToKey(key));
}
bool Keyboard::IsKeyNamePressed(const std::string &name_) {
	if ( name_.length() == 1 ) return IsKeyCharPressed(name_[0]);
	else {
		std::string name = StringToLowercase(name_);
		if ( StringMatches(name, "space") ) return IsKeyPressed(PHOENIX_KEY_SPACE);
		else if ( StringMatches(name, "lshift") ) return IsKeyPressed(PHOENIX_KEY_LEFT_SHIFT);
		else if ( StringMatches(name, "rshift") ) return IsKeyPressed(PHOENIX_KEY_RIGHT_SHIFT);
		else if ( StringMatches(name, "enter") ) return IsKeyPressed(PHOENIX_KEY_ENTER);
		else if ( StringMatches(name, "left") ) return IsKeyPressed(PHOENIX_KEY_LEFT);
		else if ( StringMatches(name, "right") ) return IsKeyPressed(PHOENIX_KEY_RIGHT);
		else if ( StringMatches(name, "up") ) return IsKeyPressed(PHOENIX_KEY_UP);
		else if ( StringMatches(name, "down") ) return IsKeyPressed(PHOENIX_KEY_DOWN);
		else if ( StringMatches(name, "tab") ) return IsKeyPressed(PHOENIX_KEY_TAB);
		else return false;
	}
}


Key gui::CharToKey(char c) {
	
	// Range shortcuts
	if      ( c >= 'A' && c <= 'Z' ) return Key(PHOENIX_KEY_A + (c - 'A'));
	else if ( c >= 'a' && c <= 'z' ) return Key(PHOENIX_KEY_A + (c - 'a'));
	else if ( c >= '0' && c <= '9' ) return Key(PHOENIX_KEY_0 + (c - '0'));
	
	// Some other characters
	else switch ( c ) {
		case ' ': return PHOENIX_KEY_SPACE;
		case '\t': return PHOENIX_KEY_TAB;
		case '\n': return PHOENIX_KEY_ENTER;
		case '[' : return PHOENIX_KEY_LEFT_BRACKET;
		case ']' : return PHOENIX_KEY_RIGHT_BRACKET;
		case '\\' : return PHOENIX_KEY_BACKSLASH;
		case ';' : return PHOENIX_KEY_SEMICOLON;
		case '\'' : return PHOENIX_KEY_APOSTROPHE;
		case ',' : return PHOENIX_KEY_COMMA;
		case '.' : return PHOENIX_KEY_PERIOD;
		case '/' : return PHOENIX_KEY_SLASH;
		case '`' : return PHOENIX_KEY_GRAVE;
		default: return PHOENIX_KEY_UNKNOWN;
	}
}
char gui::KeyToChar(Key k) {
	
	// Range shortcuts
	if      ( k >= PHOENIX_KEY_A && k <= PHOENIX_KEY_Z ) return (char)(k - PHOENIX_KEY_A) + 'A';
	else if ( k >= PHOENIX_KEY_0 && k <= PHOENIX_KEY_0 ) return (char)(k - PHOENIX_KEY_0) + '0';
	
	// Some other keys
	else switch ( k ) {
		case PHOENIX_KEY_SPACE : return ' ';
		case PHOENIX_KEY_TAB : return '\t';
		case PHOENIX_KEY_ENTER : return '\n';
		case PHOENIX_KEY_APOSTROPHE : return '\'';
		case PHOENIX_KEY_BACKSLASH : return '\\';
		case PHOENIX_KEY_COMMA : return ',';
		case PHOENIX_KEY_GRAVE : return '`';
		case PHOENIX_KEY_LEFT_BRACKET : return '[';
		case PHOENIX_KEY_RIGHT_BRACKET : return ']';
		case PHOENIX_KEY_SEMICOLON : return ';';
		case PHOENIX_KEY_PERIOD : return '.';
		case PHOENIX_KEY_SLASH : return '/';
		default: return '\0';
	}
}






void Keyboard::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<Keyboard>("Keyboard")
	.addFunction("IsKeyPressed", &Keyboard::IsKeyNamePressed)
	.endClass();
	
}









