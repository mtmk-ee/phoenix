//
//  FontRenderer.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef FontRenderer_hpp
#define FontRenderer_hpp

#include <map>
#include <string>
#include <ft2build.h>
#
#include FT_FREETYPE_H
#include "Shader.hpp"
#include "Texture.hpp"



namespace phoenix {
	namespace video {
		
		
		class FontRenderer {
//			struct Character {
//				GLuint texture_id;
//				IVec2 size;
//				IVec2 bearing;
//				GLuint advance;
//			};
//			
//			struct Font {
//				FontRenderer *renderer;
//				FT_Face font;
//				std::map<int, std::map<char, Character>> characters; // Sorted by size, then character
//				std::string font_file;
//				
//				ShaderProgram *program;
//				
//				Font(FontRenderer *renderer, const std::string &font_name, const std::string &font_file);
//				~Font();
//				
//				void LoadSize(int size);
//				inline Character& GetCharacter(int size, char c) {
//					LoadSize(size);
//					return characters[size][c];
//				}
//			};
//			
//			
//			FT_Library library;
//			std::map<std::string, Font*> fonts;
//			
//			GLuint vao;
//			GLuint vbo;
//			
//			
//			
		public:
//			FontRenderer();
//			~FontRenderer();
//			
//			
//			void LoadFont(const std::string &name, const std::string &truetype_file);
//			
//			void RenderText(const std::string &font_name, const std::string &text, const FVec2 &position, int size, float scale, const FVec3 &color);
//			
//			
			static void Wrap(scripting::Script *script);
		};
		
		
		
	}
}

#endif /* FontRenderer_hpp */
