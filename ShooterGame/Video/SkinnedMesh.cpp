//
//  SkinnedMesh.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/24/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "SkinnedMesh.hpp"
#include "../Scripting/Script.hpp"
#include "../Util/Debug.hpp"
#include "../Engine.hpp"

using namespace phoenix;
using namespace phoenix::video;


#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

/** Converts a 4x4 Assimp matrix to a GLM matrix */
inline FMat4 MatrixAIToGLM(const aiMatrix4x4 &ai_matrix) {
	FMat4 glm_matrix;
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			glm_matrix[r][c] = ai_matrix[c][r];
	
	return glm_matrix;
}
/** Converts a 3x3 Assimp matrix to a GLM matrix */
inline FMat3 MatrixAIToGLM(const aiMatrix3x3 &ai_matrix) {
	FMat3 glm_matrix;
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			glm_matrix[r][c] = ai_matrix[c][r];
	
	return glm_matrix;
}


std::map<std::string, SkinnedMeshBase*> SkinnedMeshBase::loaded_bases = std::map<std::string, SkinnedMeshBase*>();


FMat4 Bone::GetParentTransform() {
	if ( parent != nullptr)
		return parent->global_transform;
	else
		return FMat4();
}


void Bone::WrapBone(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<Bone>("Bone")
	.addData("global_transform", &Bone::global_transform)
	.addData("transform", &Bone::transform)
	.addData("local_transform", &Bone::local_transform)
	.addData("final_transform", &Bone::final_transform)
	.addData("offset_transform", &Bone::offset_transform)
	.addData("parent", &Bone::parent)
	.addData("name", &Bone::name);
	
}






SkinnedMesh::SkinnedMesh(const std::string &name) : model_name(name) {
	std::string shader_path = Engine::GetCurrent()->GetPlatform()->GetGameFolder() + "/Shaders/" + model_name + "/" + model_name;
	ShaderSource *vertex_shader = ShaderSource::Load(shader_path + ".vert", 0);
	ShaderSource *frag_shader = ShaderSource::Load(shader_path + ".frag", 1);
	
	program = new ShaderProgram();
	program->AttachShader(vertex_shader);
	program->AttachShader(frag_shader);
	program->LinkProgram();
	
	delete vertex_shader;
	delete frag_shader;
	
	// Set model matrix
	SetModelMatrix(FMat4());
	SetScaleMatrix(FMat4());
	SetCorrectionMatrix(FMat4());
}
SkinnedMesh::~SkinnedMesh() {
	delete program;
}

bool SkinnedMesh::LoadMesh(const std::string &file) {
	
	// If the mesh is already loaded, search for it and reuse it
	if ( SkinnedMeshBase::loaded_bases.find(file) != SkinnedMeshBase::loaded_bases.end() ) {
		base = SkinnedMeshBase::loaded_bases[file];
		
		// Add some transforms to the transform list
		for (int i = 0; i < base->final_transform_count; ++i) {
			bone_final_transforms.push_back(FMat4());
		}
		
		// Load root bone
		root_bone = new Bone(this);
		root_bone->name = base->scene->mRootNode->mName.C_Str();
		LoadBones(base->scene->mRootNode, nullptr, root_bone);
		
		return true;
	}
	// The requested mesh isn't already loaded, so create a new one and load it
	else {
		// Create a new assimp importer
		Assimp::Importer *importer = new Assimp::Importer();
		
		// Create a new skinned mesh base and set some defaults
		base = new SkinnedMeshBase();
		base->num_bones = 0;
		base->importer = importer;
		
		// Import the scene from the file
		base->scene = importer->ReadFile(file.c_str(), aiProcess_ImproveCacheLocality | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals);
		
		
		// Set the mesh base
		SkinnedMeshBase::loaded_bases[file] = base;
		
		if ( base->scene != nullptr ) {
			base->inverse_global_transform = glm::inverse(MatrixAIToGLM(base->scene->mRootNode->mTransformation));
			base->final_transform_count = 0;
			
			// Load the scene mesh by mesh
			int vertex_count = 0, index_count = 0;
			for (int i = 0; i < base->scene->mNumMeshes; ++i) {
				aiMesh *mesh = base->scene->mMeshes[i];
				
				// Create a new entry for this mesh
				MeshEntry entry;
				entry.base_vertex = vertex_count;
				entry.base_index = index_count;
				entry.num_indices = mesh->mNumFaces * 3;
				entry.material_index = mesh->mMaterialIndex;
				base->entries.push_back(entry);
				
				
				// Vertices
				for (int j = 0; j < mesh->mNumVertices; ++j) {
					SkinnedVertex vertex;
					
					// Set vertex position
					vertex.position.x = mesh->mVertices[j].x;
					vertex.position.y = mesh->mVertices[j].y;
					vertex.position.z = mesh->mVertices[j].z;
					
					// Set vertex normal
					vertex.normal.x = mesh->mNormals[j].x;
					vertex.normal.y = mesh->mNormals[j].y;
					vertex.normal.z = mesh->mNormals[j].z;
					
					// Set vertex texture coordinates
					if ( mesh->HasTextureCoords(0) ) {
						vertex.uv.x = mesh->mTextureCoords[0][j].x;
						vertex.uv.y = mesh->mTextureCoords[0][j].y;
					}
					else {
						vertex.uv = FVec2(0, 0);
					}
					
					// Add the new vertex to the list
					base->vertices.push_back(vertex);
				}
				
				// Faces
				for (int j = 0; j < mesh->mNumFaces; ++j) {
					const aiFace& face = mesh->mFaces[j];
					base->indices.push_back(face.mIndices[0]);
					base->indices.push_back(face.mIndices[1]);
					base->indices.push_back(face.mIndices[2]);
				}
				
				for (int j = 0; j < mesh->mNumBones; ++j) {
					int bone_index = 0;
					std::string bone_name = mesh->mBones[j]->mName.C_Str();
					
					if ( base->bone_mapping.find(bone_name) == base->bone_mapping.end() ) {
						// Allocate an index for a new bone
						bone_index = base->num_bones;
						base->num_bones++;
						
						// Load bone matrices
						base->bone_offsets.push_back(MatrixAIToGLM(mesh->mBones[j]->mOffsetMatrix));
						base->final_transform_count++;
						bone_final_transforms.push_back(FMat4(1.0f));
						
						base->bone_mapping[bone_name] = bone_index;
					}
					else {
						bone_index = base->bone_mapping[bone_name];
					}
					
					// Load the bone data (weights + bone ids)
					for (int k = 0; k < mesh->mBones[j]->mNumWeights; ++k) {
						int vertex_id = base->entries[i].base_vertex + mesh->mBones[j]->mWeights[k].mVertexId;
						float weight = mesh->mBones[j]->mWeights[k].mWeight;
						base->vertices[vertex_id].AddBoneData(bone_index, weight);
					}
				}
				
				// Increment the vertex and index count so we can store them in the base vertex/index variables
				vertex_count += mesh->mNumVertices;
				index_count += mesh->mNumFaces * 3;
			}
			
			
			// Load root bone
			root_bone = new Bone(this);
			root_bone->name = base->scene->mRootNode->mName.data;
			LoadBones(base->scene->mRootNode, nullptr, root_bone);
			UpdateSkeleton();
			//PrintBoneHierarchy(root_bone);
			
			
			
			// Get the directory from the file path
			std::string::size_type slash_index = file.find_last_of("/");
			std::string dir;
			
			if ( slash_index == std::string::npos ) dir = ".";
			else if ( slash_index == 0 ) dir = "/";
			else dir = file.substr(0, slash_index);
			
			
			// Resize the material vector
			base->materials.resize(base->scene->mNumMaterials);
			
			for (int i = 0 ; i < base->scene->mNumMaterials ; i++) {
				const aiMaterial *material = base->scene->mMaterials[i];
				base->materials[i] = nullptr;
				
				// Load diffuse texture from the material
				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
					aiString path;
					
					if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
						std::string p(path.data);
						
						if (p.substr(0, 2).compare(".\\") == 0) {
							p = p.substr(2, p.size() - 2);
						}
						
						// Load the texture into the material vector
						base->materials[i] = Texture::Load(GL_TEXTURE_2D, dir + "/" + p);
					}
				}
			}
			
			// Generate vertex arrays and buffers
			glGenVertexArrays(1, &base->vao);
			glBindVertexArray(base->vao);
			glGenBuffers(1, &base->vbo);
			glGenBuffers(1, &base->ebo);
			
			// Upload the vertex data to the GPU
			glBindBuffer(GL_ARRAY_BUFFER, base->vbo);
			glBufferData(GL_ARRAY_BUFFER, base->vertices.size() * sizeof(SkinnedVertex), &base->vertices[0], GL_STATIC_DRAW);
			
			// Positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex), (GLvoid*)0);
			
			// Normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex), (GLvoid*)offsetof(SkinnedVertex, normal));
			
			// UVs
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex), (GLvoid*)offsetof(SkinnedVertex, uv));
			
			// Bone weights
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex), (GLvoid*)offsetof(SkinnedVertex, bone_weights));
			
			
			// Bone indices
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex), (GLvoid*)offsetof(SkinnedVertex, bone_indices));
			
			// Upload the index buffer data
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, base->ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, base->indices.size() * sizeof(uint), &base->indices[0], GL_STATIC_DRAW);
			
			
			glBindVertexArray(0);
			
			return true;
		}
		else return false;
	}
}

void SkinnedMesh::LoadBones(aiNode *node, Bone *parent, Bone *new_bone) {
	
	// If there is no parent, load this bone as the root bone
	if ( parent == nullptr ) {
		new_bone->bone_index = -1;
		new_bone->global_transform = FMat4();
		new_bone->transform = MatrixAIToGLM(node->mTransformation);
		new_bone->offset_transform = FMat4();
		new_bone->final_transform = FMat4();
	}
	
	
	// Load child bones
	for (int i = 0; i < node->mNumChildren; ++i) {
		aiNode *child = node->mChildren[i];
		std::string child_name = child->mName.C_Str();
		
		
		// Allocate a new bone
		Bone *child_bone = new_bone->NewBone(child_name);
		if ( base->bone_mapping.find(child_name) == base->bone_mapping.end() ) {
			child_bone->bone_index = -1;
			child_bone->offset_transform = FMat4();
		}
		else {
			// Load bone matrices
			child_bone->global_transform = FMat4();
			child_bone->final_transform = FMat4();
			child_bone->bone_index = base->bone_mapping[child_name];
			child_bone->transform = MatrixAIToGLM(child->mTransformation);
			child_bone->offset_transform = base->bone_offsets[child_bone->bone_index];
		}
		child_bone->transform = MatrixAIToGLM(child->mTransformation);
		
		// Load the child bone
		LoadBones(child, new_bone, child_bone);
	}
}
void SkinnedMesh::UpdateBone(Bone *bone) {
	if ( bone != nullptr ) {
		if ( bone->bone_index != -1 ) {
			
			// Recalculate bone matrices
			bone->global_transform = bone->GetParentTransform() * bone->transform * bone->local_transform;
			bone->final_transform = base->inverse_global_transform * bone->global_transform * bone->offset_transform;
			bone->final_transform = correction_matrix * bone->final_transform;
			
			bone_final_transforms[bone->bone_index] = bone->final_transform;
		}
		
		// Update child bones
		for (auto pair : bone->children) {
			UpdateBone(pair.second);
		}
	}
}
void SkinnedMesh::UpdateSkeleton() {
	UpdateBone(root_bone);
}


Bone* SkinnedMesh::FindBone(Bone *bone, const std::string &name) {
	if ( bone == nullptr ) return nullptr;
	if ( bone->name.compare(name) == 0 ) return bone;
	
	// Search child bones for a bone with the given name
	for (auto pair : bone->children) {
		Bone *result = FindBone(pair.second, name);
		if ( result != nullptr ) return result;
	}
	
	// The bone wasn't found, so log an error and return nullptr
	LogError("Unrecognized bone name '%s'", name.c_str());
	return nullptr;
}

FVec3 SkinnedMesh::GetBoneAngle(phoenix::video::Bone *a, phoenix::video::Bone *b) {
	
	// Get the final transform for both bones
	FMat4 transform_a = a->final_transform;
	FMat4 transform_b = b->final_transform;
	
	// Get the translation of each bone
	FVec3 translation_a = VectorFVec4ToFVec3(transform_a[3]);
	FVec3 translation_b = VectorFVec4ToFVec3(transform_b[3]);
	FVec3 dir = glm::normalize(translation_b - translation_a);
	
	// Store the direction components into individual variables for easy access
	float dx = dir.x;
	float dy = dir.y;
	float dz = dir.z;
	
	
	// Calculate euler angles
	float pitch = atan2f(dx, dy) * 180 / AI_MATH_PI;
	float yaw = atan2f(dz, sqrtf(dx * dx + dy * dy)) * 180 / AI_MATH_PI;
	
	
	return FVec3(pitch, yaw, 0);
}


void SkinnedMesh::ApplyBoneTransform(const std::string &bone_name, const FMat4 &transformation) {
	Bone *bone = GetBone(bone_name);
	
	if ( bone != nullptr )
		bone->local_transform = transformation * bone->local_transform;
}
void SkinnedMesh::SetBoneTransform(const std::string &bone_name, const FMat4 &transform) {
	Bone *bone = GetBone(bone_name);
	
	if ( bone != nullptr )
		bone->local_transform = transform;
}


void SkinnedMesh::Render(Camera *camera) {
	program->UseProgram();
	
	// Set shader program uniforms
	program->SetUniformInt("color_map", 0);
	program->SetUniformFVec3("camera_pos", camera->GetPosition());
	program->SetUniformFMat4("projection", camera->GetProjectionMatrix());
	program->SetUniformFMat4("view", camera->GetViewMatrix());
	program->SetUniformFMat4("model", model_matrix * scale_matrix);
	program->SetUniform("bones", &bone_final_transforms[0], base->num_bones);
	
	// Enable blending functions for transparent materials
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Bind the vertex array
	glBindVertexArray(base->vao);
	
	
	// Draw each mesh
	for (int i = 0; i < base->entries.size(); ++i) {
		int material_index = base->entries[i].material_index;
		
		// Bind the material texture for this mesh
		if ( material_index < base->materials.size() && base->materials[material_index] != nullptr ) {
			base->materials[material_index]->Bind(GL_TEXTURE0);
		}
		
		// Draw the mesh
		glDrawElementsBaseVertex(GL_TRIANGLES,
								 base->entries[i].num_indices,
								 GL_UNSIGNED_INT,
								 (GLvoid*)(sizeof(uint) * base->entries[i].base_index),
								 base->entries[i].base_vertex);
	}
	
	glBindVertexArray(0);
	program->UnbindProgram();
}



void SkinnedMesh::Wrap(scripting::Script *script) {
	Bone::WrapBone(script);
	
	script->GetGlobalNamespace()
	.beginClass<SkinnedMesh>("SkinnedMesh")
	.addConstructor<void (*)(const std::string&)>()
	.addFunction("GetShaderProgram", &SkinnedMesh::GetShaderProgram)
	.addFunction("LoadMesh", &SkinnedMesh::LoadMesh)
	.addFunction("Render", &SkinnedMesh::Render)
	.addFunction("UpdateSkeleton", &SkinnedMesh::UpdateSkeleton)
	.addFunction("GetBone", &SkinnedMesh::GetBone)
	.addFunction("GetBoneAngle", &SkinnedMesh::GetBoneAngle)
	
	.addFunction("SetBoneTransform", &SkinnedMesh::SetBoneTransform)
	.addFunction("ApplyBoneTransform", &SkinnedMesh::ApplyBoneTransform)
	.addFunction("GetBoneFinalTransform", &SkinnedMesh::GetBoneFinalTransform)
	.addFunction("GetBoneLocalTransform", &SkinnedMesh::GetBoneLocalTransform)
	.addFunction("GetBoneGlobalTransform", &SkinnedMesh::GetBoneGlobalTransform)
	
	.addFunction("SetModelMatrix", &SkinnedMesh::SetModelMatrix)
	.addFunction("SetCorrectionMatrix", &SkinnedMesh::SetCorrectionMatrix)
	.addFunction("SetScaleMatrix", &SkinnedMesh::SetScaleMatrix)
	.addFunction("GetModelMatrix", &SkinnedMesh::GetModelMatrix)
	.addFunction("GetCorrectionMatrix", &SkinnedMesh::GetCorrectionMatrix)
	.endClass();
	
	
}


