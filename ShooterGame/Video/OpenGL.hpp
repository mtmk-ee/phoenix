//
//  OpenGL.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/23/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef OpenGL_hpp
#define OpenGL_hpp

#include <OpenGL/gl3.h>

namespace phoenix {
	namespace video {
		
#define INVALID_UNIFORM_LOCATION 0xffffffff
		
		
		
		/** Prints out all OpenGL errors */
		void PrintOpenGLErrors();
		
		
		
	}
}



#endif /* OpenGL_hpp */
