//
//  GLFW.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef GLFW_hpp
#define GLFW_hpp

#include <GLFW/glfw3.h>


namespace phoenix {
	namespace gui {
		
		/** GLFW access */
		class GLFW {
			static GLFW instance;
			bool init;
			
			// Private constructor and destructor
			GLFW();
			~GLFW();
			
		public:
			
			/** Initializes GLFW */
			static void Init();
			/** Checks if GLFW was initialized */
			static inline bool IsInit() {
				return instance.init;
			}
			
		};
		
		
	}
}

#endif /* GLFW_hpp */
