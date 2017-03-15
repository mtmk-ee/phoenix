//
//  FontRenderer.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "FontRenderer.hpp"
#include "../Util/Debug.hpp"
#include "../Scripting/Script.hpp"
#include "../Engine.hpp"
#include <OpenGL/gl3.h>
using namespace phoenix::video;



//FontRenderer::Font::Font(FontRenderer *renderer, const std::string &font_name, const std::string &font_file) : renderer(renderer), font_file(font_file) {
//	
//	if ( FT_New_Face(renderer->library, font_file.c_str(), 0, &font) ) {
//		LogError("Failed to load font '%s'", font_file.c_str());
//	}
//	
//	
//	std::string font_folder = Engine::GetCurrent()->GetPlatform()->GetGameFolder() + "/Shaders/Fonts/" + font_name;
//	
//	program = new ShaderProgram();
//	program->LoadSource(font_folder + "/" + font_name + ".vert", 0);
//	program->LoadSource(font_folder + "/" + font_name + ".frag", 0);
//	program->LinkProgram();
//}
//FontRenderer::Font::~Font() {
//	FT_Done_Face(font);
//	delete program;
//	
//	for (auto character_list : characters) {
//		for (int i = 0; i < 128; ++i) {
//			glDeleteTextures(1, &character_list.second[(char)i].texture_id);
//		}
//	}
//}
//
//
//void FontRenderer::Font::LoadSize(int size) {
//	// Check if the font size is already loaded
//	if ( characters.find(size) != characters.end() ) return;
//	
//	// Load characters
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	
//	for (int c = 0; c < 128; ++c) {
//		if ( FT_Load_Char(font, (char)c, FT_LOAD_RENDER) ) {
//			LogError("Unable to load character '%c' in font '%s'", c, font_file.c_str());
//			continue;
//		}
//		
//		// Load texture
//		GLuint texture_id;
//		glGenTextures(1, &texture_id);
//		glBindTexture(GL_TEXTURE_2D, texture_id);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font->glyph->bitmap.width, font->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, font->glyph->bitmap.buffer);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		
//		Character character = {
//			texture_id,
//			IVec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
//			IVec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
//			(GLuint)(font->glyph->advance.x)
//		};
//		characters[size][(char)c] = character;
//	}
//}
//
//
//FontRenderer::FontRenderer() {
//	if ( FT_Init_FreeType(&library) ) {
//		LogError("Could not load FreeType library");
//	}
//	
//	
//	glGenVertexArrays(1, &vao);
//	glGenBuffers(1, &vbo);
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//FontRenderer::~FontRenderer() {
//	glDeleteVertexArrays(1, &vao);
//	glDeleteBuffers(1, &vbo);
//}
//
//
//void FontRenderer::LoadFont(const std::string &name, const std::string &truetype_file) {
//	if ( fonts.find(name) == fonts.end() )
//		fonts[name] = new Font(this, name, truetype_file);
//}
//
//
//void FontRenderer::RenderText(const std::string &font_name, const std::string &text, const FVec2 &position_, int size, float scale, const FVec3 &color) {
//	Font *font = fonts[font_name];
//	
//	font->program->UseProgram();
//	font->program->SetUniformFVec3("text_color", color);
//	glActiveTexture(0);
//	glBindVertexArray(vao);
//	
//	
//	
//	FVec2 position = position_;
//	
//	for (char c : text) {
//		const Character &character = font->GetCharacter(size, c);
//		
//		float x = position.x + character.bearing.x * scale;
//		float y = position.y - (character.size.y - character.bearing.y) * scale;
//		
//		float w = character.size.x * scale;
//		float h = character.size.y * scale;
//		
//		GLfloat vertices[6][4] = {
//			{ x,     y + h,   0.0, 0.0 },
//			{ x,     y,       0.0, 1.0 },
//			{ x + w, y,       1.0, 1.0 },
//			
//			{ x,     y + h,   0.0, 0.0 },
//			{ x + w, y,       1.0, 1.0 },
//			{ x + w, y + h,   1.0, 0.0 }
//		};
//		
//		glBindTexture(GL_TEXTURE_2D, character.texture_id);
//		
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		
//		position.x += (character.advance >> 6) * scale;
//	}
//	
//	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//

void FontRenderer::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<FontRenderer>("FontRenderer")
//	.addFunction("RenderText", &FontRenderer::RenderText)
	.endClass();
}






