//
//  Model.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/20/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Model.hpp"
#include "../Util/File.hpp"
#include "../Util/Debug.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix::video;







Model::Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
				  const std::vector<Texture*> &textures) : vertices(vertices), indices(indices), textures(textures) {
	Init();
}


void Model::Mesh::Init() {
	
	
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	
	glBindVertexArray(0);
	
	
}


void Model::Mesh::Render(phoenix::video::ShaderProgram *program) {
	
	GLuint diffuse_count = 1, specular_count = 1;
	
	for (GLuint i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		
		//		std::string name = textures[i]->GetType();
		//		int number = 0;
		//
		//		if ( name.compare("diffuse") == 0 )
		//			number = diffuse_count++;
		//		else if ( name.compare("specular") == 0 )
		//			number = specular_count++;
		//
		//		program->SetUniformFloat("material." + name + std::to_string(number), i);
		//		glBindTexture(GL_TEXTURE_2D, textures[i]->GetID());
		
	}
	glActiveTexture(GL_TEXTURE0);
	
	
	// Draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}





Model::~Model() {
	
	
	
	
}

void Model::Render(phoenix::video::ShaderProgram *program) {
	for (Mesh *mesh : meshes) {
		mesh->Render(program);
	}
}


Model* Model::Load(const std::string &path) {
	
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if ( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) {
		LogError("Could not load model: '%s'", path.c_str());
		return nullptr;
	}
	else {
		return new Model(scene, File(path).GetParent().GetPath());
	}
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
	
	for (GLuint i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	
	for(GLuint i = 0; i < node->mNumChildren; ++i) {
		ProcessNode(node->mChildren[i], scene);
	}
}
Model::Mesh* Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture*> textures;
	
	for (GLuint i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		
		// Positions
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.vertex = vector;
		
		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;
		
		// Texture Coordinates
		if ( mesh->mTextureCoords[0] ) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = vec;
		}
		else
			vertex.uv = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	// Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	// Process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	
	// 1. Diffuse maps
	std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. Specular maps
	std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	
	// Return a mesh object created from the extracted mesh data
	return new Mesh(vertices, indices, textures);
}


std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string type_name) {
	std::vector<Texture*> textures;
	for (GLuint i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);
		
		GLboolean skip = false;
		for (GLuint j = 0; j < loaded_textures.size(); j++)
		{
			if ( std::strcmp(loaded_textures[j]->GetPath().c_str(), str.C_Str()) == 0 ) {
				textures.push_back(loaded_textures[j]);
				skip = true;
				break;
			}
		}
		if(!skip)
		{   // If texture hasn't been loaded already, load it
			//			Texture* texture = Texture::Load(str.C_Str(), type_name);
			//			textures.push_back(texture);
			//			loaded_textures.push_back(texture);
		}
	}
	return textures;
}



void Model::Wrap(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<Model>("Model")
	.addStaticFunction("Load", Model::Load)
	.addFunction("Render", &Model::Render)
	.endClass();
	
}





