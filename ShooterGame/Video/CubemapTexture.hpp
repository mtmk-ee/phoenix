//
//  CubemapTexture.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/10/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef CubemapTexture_hpp
#define CubemapTexture_hpp

#include "OpenGL.hpp"
#include "../Util/Vector.hpp"
#include <string>

namespace phoenix {
	namespace video {
		
		
		/** Information about loading a cubemap texture */
		struct CubemapTextureInfo {
			std::string posx_path;
			std::string negx_path;
			std::string posy_path;
			std::string negy_path;
			std::string posz_path;
			std::string negz_path;
			
			static void Wrap(scripting::Script *script);
		};
		
		
		/** A cubemap texture */
		class CubemapTexture {
			GLuint tex_id;
			
			inline CubemapTexture(GLuint tex_id) : tex_id(tex_id) { }
		public:
			/** Loads a cubemap texture, given a CubemapTextureInfo instance */
			static CubemapTexture *Load(const CubemapTextureInfo &texture_info);
			~CubemapTexture();
			
			
			/** Binds the texture */
			void Bind();
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
		
	}
}

#endif /* CubemapTexture_hpp */
