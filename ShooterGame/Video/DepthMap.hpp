//
//  DepthMap.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef DepthMap_hpp
#define DepthMap_hpp

#include "OpenGL.hpp"
#include <cstdlib>

namespace phoenix {
	namespace video {
		
		
		class DepthMap {
			GLuint fbo;
			GLuint depth_map;
			int width, height;
			
			
		public:
			DepthMap(int width, int height);
			
			void BindTexture();
			void UseFramebuffer();
			
			void SetFramebufferViewport();
			void SetDisplayViewport();
			
		};
		
	}
}

#endif /* DepthMap_hpp */
