//
//  Texture.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "OpenGL.hpp"
#include <string>


namespace phoenix {
	namespace scripting { class Script; }
	
	
	namespace video {
		
		
		
		/** A class used to texture a model */
		class Texture {
			GLenum target;
			GLuint tex_id;
			int width, height;
			std::string path;
			
			inline Texture(GLenum target, GLuint tex_id, int width, int height, const std::string &path) : target(target), tex_id(tex_id), width(width), height(height), path(path) { }
			
		public:
			static Texture *Load(GLenum target, const std::string &file);
			~Texture();
			
			
			/** Returns the path this texture was loaded from */
			inline std::string GetPath() {
				return path;
			}
			/** Returns the OpenGL ID of this texture */
			inline GLuint GetID() const {
				return tex_id;
			}
			
			
			
			/** Returns the width of the texture */
			inline int GetWidth() const {
				return width;
			}
			/** Returns the height of the texture */
			inline int GetHeight() const {
				return height;
			}
			
			
			
			/** Binds this texture */
			void Bind(GLenum tex_unit);
			/** Unbinds texture */
			void Unbind();
			
			
			
			static void Wrap(scripting::Script *script);
			
		};
		
		
		
		
		
		
	}
}

#endif /* Texture_hpp */
