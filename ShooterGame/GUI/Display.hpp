//
//  Display.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include "Input.hpp"
#include "../Util/Vector.hpp"

namespace phoenix {
	class Engine;
	namespace scripting { class Script; }
	
	
	
	namespace gui {
		
		
		
		
		
		
		
		
		/** A display to draw on */
		class Display {
			void *window;
			Keyboard keyboard;
			Mouse mouse;
			
			
			
			Display(void *window);
			
			
		public:
			/** Creates a new display */
			static Display* New();
			~Display();
			
			/** Returns the GLFW window handle */
			inline void *GetWindowHandle() {
				return window;
			}
			
			/** Sets the clear color for the window */
			void SetClearColor(float r, float g, float b, float a);
			
			/** Returns the keyboard */
			inline Keyboard* GetKeyboard() {
				return &keyboard;
			}
			/** Returns the mouse */
			inline Mouse* GetMouse() {
				return &mouse;
			}
			
			/** Sets if the mouse is captured or not */
			void CaptureMouse(bool captured);
			
			
			
			
			/** Sets the window title */
			void SetTitle(const std::string &name);
			/** Sets the window size */
			void SetSize(const IVec2 &size);
			/** Sets the window location */
			void SetLocation(const IVec2 &location);
			/** Gets the window size */
			IVec2 GetSize();
			/** Gets the window location */
			IVec2 GetLocation();
			
			
			/** Maximizes the window */
			void Maximize();
			/** Makes the window's OpenGL context current */
			void MakeCurrent();
			
			
			/** Begins the rendering process */
			void BeginRender();
			/** Finishes the rendering process */
			void FinishRender();
			/** Polls window events */
			void PollEvents(Engine *engine);
			
			
			
			static void Wrap(scripting::Script *script);
			
		};
		
		
		
		
		
		
		
		
	}
}

#endif /* Display_hpp */
