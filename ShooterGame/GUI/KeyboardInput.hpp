//
//  KeyboardInput.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef KeyboardInput_hpp
#define KeyboardInput_hpp

#include <string>


namespace phoenix {
	namespace scripting { class Script; }
	
	
	namespace gui {
		class Display;
		
		
		
		// Keyboard enum
		enum Key {
			PHOENIX_KEY_UNKNOWN = -1,
			
			PHOENIX_KEY_SPACE = 32,
			PHOENIX_KEY_APOSTROPHE = 39,
			PHOENIX_KEY_COMMA = 44,
			PHOENIX_KEY_MINUS = 45,
			PHOENIX_KEY_PERIOD = 46,
			PHOENIX_KEY_SLASH = 47,
			PHOENIX_KEY_SEMICOLON = 59,
			PHOENIX_KEY_EQUALS = 61,
			PHOENIX_KEY_LEFT_BRACKET = 91,
			PHOENIX_KEY_BACKSLASH = 92,
			PHOENIX_KEY_RIGHT_BRACKET = 93,
			PHOENIX_KEY_GRAVE = 94,
			
			PHOENIX_KEY_0 = 48,
			PHOENIX_KEY_1,
			PHOENIX_KEY_2,
			PHOENIX_KEY_3,
			PHOENIX_KEY_4,
			PHOENIX_KEY_5,
			PHOENIX_KEY_6,
			PHOENIX_KEY_7,
			PHOENIX_KEY_8,
			PHOENIX_KEY_9,
			
			PHOENIX_KEY_A = 65,
			PHOENIX_KEY_B,
			PHOENIX_KEY_C,
			PHOENIX_KEY_D,
			PHOENIX_KEY_E,
			PHOENIX_KEY_F,
			PHOENIX_KEY_G,
			PHOENIX_KEY_H,
			PHOENIX_KEY_I,
			PHOENIX_KEY_J,
			PHOENIX_KEY_K,
			PHOENIX_KEY_L,
			PHOENIX_KEY_M,
			PHOENIX_KEY_N,
			PHOENIX_KEY_O,
			PHOENIX_KEY_P,
			PHOENIX_KEY_Q,
			PHOENIX_KEY_R,
			PHOENIX_KEY_S,
			PHOENIX_KEY_T,
			PHOENIX_KEY_U,
			PHOENIX_KEY_V,
			PHOENIX_KEY_W,
			PHOENIX_KEY_X,
			PHOENIX_KEY_Y,
			PHOENIX_KEY_Z,
			
			PHOENIX_KEY_F1 = 290,
			PHOENIX_KEY_F2,
			PHOENIX_KEY_F3,
			PHOENIX_KEY_F4,
			PHOENIX_KEY_F5,
			PHOENIX_KEY_F6,
			PHOENIX_KEY_F7,
			PHOENIX_KEY_F8,
			PHOENIX_KEY_F9,
			PHOENIX_KEY_F10,
			PHOENIX_KEY_F11,
			PHOENIX_KEY_F12,
			
			PHOENIX_KEY_ESCAPE = 256,
			PHOENIX_KEY_ENTER = 257,
			PHOENIX_KEY_TAB = 258,
			PHOENIX_KEY_BACKSPACE = 259,
			PHOENIX_KEY_INSERT = 260,
			PHOENIX_KEY_DELETE = 261,
			PHOENIX_KEY_RIGHT = 262,
			PHOENIX_KEY_LEFT,
			PHOENIX_KEY_DOWN,
			PHOENIX_KEY_UP,
			
			PHOENIX_KEY_CAPS_LOCK = 280,
			PHOENIX_KEY_LEFT_SHIFT = 340,
			PHOENIX_KEY_LEFT_CONTROL,
			PHOENIX_KEY_LEFT_ALT,
			PHOENIX_KEY_LEFT_META,
			PHOENIX_KEY_RIGHT_SHIFT,
			PHOENIX_KEY_RIGHT_CONTROL,
			PHOENIX_KEY_RIGHT_ALT,
			PHOENIX_KEY_RIGHT_META,
		};
		
		
		
		/** Keyboard class */
		class Keyboard {
			Display *display;
			
		public:
			Keyboard(Display *display);
			
			
			/** Checks if a key was pressed using the Key enum */
			bool IsKeyPressed(Key key);
			/** Checks if a key was pressed using the Key char */
			bool IsKeyCharPressed(char key);
			/** Checks if a key was pressed using the Key's name */
			bool IsKeyNamePressed(const std::string &name);
			
			
			static void Wrap(scripting::Script *script);
		};
		
		/** Converts a character to a key */
		Key CharToKey(char c);
		/** Converts a key to a character */
		char KeyToChar(Key k);
		
		
		
		
		
		
	}
}

#endif /* KeyboardInput_hpp */
