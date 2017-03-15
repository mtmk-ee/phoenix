//
//  MouseInput.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef MouseInput_hpp
#define MouseInput_hpp

namespace phoenix {
	namespace scripting { class Script; }
	
	
	namespace gui {
		class Display;
		
		
		
		
		// Mouse enum
		enum MouseButton {
			PHOENIX_MOUSE_LEFT,
			PHOENIX_MOUSE_MIDDLE,
			PHOENIX_MOUSE_RIGHT
		};
		
		
		/** Mouse input */
		class Mouse {
			double x, y;
			double old_x, old_y;
			bool first_update;
			Display *display;
			
		public:
			Mouse(Display *display) : display(display), x(0), y(0), old_x(0), old_y(0)  { }
			
			/** Returns the delta x movement of the mouse */
			inline double GetDeltaX() {
				return x - old_x;
			}
			/** Returns the delta y movement of the mouse */
			inline double GetDeltaY() {
				return y - old_y;
			}
			/** Returns the x position of the mouse */
			inline double GetX() {
				return x;
			}
			/** Returns the y position of the mouse */
			inline double GetY() {
				return y;
			}
			
			/** Checks if a mouse button is pressed */
			bool IsButtonPressed(int button);
			
			
			/** Updates the mouse */
			void Update();
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
		
		
	}
}

#endif /* MouseInput_hpp */
