//
//  Model.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/20/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "Texture.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "OpenGL.hpp"
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include <vector>

namespace phoenix {
	namespace scripting { class Script; }
	
	
	namespace video {
		
		
		
		class Model {
			class Mesh {
				std::vector<Vertex> vertices;
				std::vector<GLuint> indices;
				std::vector<Texture*> textures;
				GLuint vao, vbo, ebo;
				
				
				void Init();
				
			public:
				Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
					 const std::vector<Texture*> &textures);
				
				
				
				void Render(ShaderProgram *program);
			};
			
			
			
			std::vector<Mesh*> meshes;
			std::vector<Texture*> loaded_textures;
			std::string directory;
			
			void ProcessNode(aiNode *node, const aiScene *scene);
			Mesh* ProcessMesh(aiMesh *mesh, const aiScene *scene);
			std::vector<Texture*> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string type_name);
			
			
			inline Model(const aiScene *scene, const std::string &directory) : directory(directory) {
				this->directory = directory;
				ProcessNode(scene->mRootNode, scene);
			};
			
			
		public:
			~Model();
			/** Loads a model */
			static Model* Load(const std::string &path);
			
			
			
			void Render(ShaderProgram *program);
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
	}
}

#endif /* Model_hpp */
