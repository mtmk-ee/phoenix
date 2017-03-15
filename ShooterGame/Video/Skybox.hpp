//
//  Skybox.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/10/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include "Camera.hpp"
#include "CubemapTexture.hpp"
#include "Vertex.hpp"
#include <vector>

namespace phoenix {
	namespace video {
		
		
		/** A skybox for a world */
		class Skybox {
			CubemapTexture *texture;
			std::vector<Vertex> vertices;
			
			GLuint vao;
			GLuint vbo;
			
			
			void LoadSkybox(float size);
			
		public:
			Skybox(CubemapTexture *texture, float size);
			~Skybox();
			
			
			/** Renders the skybox */
			void Render(Camera *camera, ShaderProgram *program);
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
		
	}
}

#endif /* Skybox_hpp */
