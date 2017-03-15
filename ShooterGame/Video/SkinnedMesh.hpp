//
//  SkinnedMesh.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/24/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef SkinnedMesh_hpp
#define SkinnedMesh_hpp


#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include <map>
#include <vector>

namespace phoenix {
	namespace video {
		class SkinnedMesh;
		
		
		/** Vertex for a skinned mesh */
		struct SkinnedVertex {
			FVec3 position;
			FVec3 normal;
			FVec2 uv;
			FVec4 bone_weights;
			FVec4 bone_indices;
			
			inline SkinnedVertex() {
				bone_weights = FVec4(0, 0, 0, 0);
				bone_indices = FVec4(0, 0, 0, 0);
			}
			
			inline void AddBoneData(int bone_id, float weight) {
				for (int i = 0; i < 4; ++i) {
					if ( bone_weights[i] == 0 ) {
						bone_indices[i] = bone_id;
						bone_weights[i] = weight;
						return;
					}
				}
			}
		};
		
		struct MeshEntry {
			uint num_indices;
			uint base_vertex;
			uint base_index;
			uint material_index;
		};
		
		
		/** A bone in a skinned mesh */
		struct Bone {
			FMat4 global_transform;
			FMat4 transform;
			FMat4 local_transform;
			
			FMat4 final_transform;
			FMat4 offset_transform;
			int bone_index;
			
			std::string name;
			
			SkinnedMesh *mesh;
			Bone *parent;
			std::map<std::string, Bone*> children;
			
			inline Bone(SkinnedMesh *mesh) : parent(nullptr), bone_index(0), mesh(mesh) {
				
			}
			inline Bone(Bone *parent) : parent(parent), bone_index(0) {
				
			}
			
			inline Bone* NewBone(const std::string &name) {
				children[name] = new Bone(this);
				children[name]->name = name;
				return children[name];
			}
			
			FMat4 GetParentTransform();
			
			
			static void WrapBone(scripting::Script *script);
		};
		
		/** Stores the information for a SkinnedMesh so we can reuse it */
		struct SkinnedMeshBase {
			static std::map<std::string, SkinnedMeshBase*> loaded_bases;
			
			GLuint vao;
			GLuint vbo;
			GLuint ebo;
			
			int num_bones;
			std::vector<SkinnedVertex> vertices;
			std::vector<int> indices;
			std::vector<MeshEntry> entries;
			std::vector<Texture*> materials;
			
			int final_transform_count;
			std::vector<FMat4> bone_offsets;
			std::map<std::string, int> bone_mapping;
			FMat4 inverse_global_transform;
			
			Assimp::Importer *importer;
			const aiScene *scene;
		};
		
		
		/** A skinned mesh */
		class SkinnedMesh {
			SkinnedMeshBase *base;
			std::string model_name;
			
			Bone *root_bone;
			std::vector<FMat4> bone_final_transforms;
			
			FMat4 model_matrix;
			FMat4 correction_matrix;
			FMat4 scale_matrix;
			
			ShaderProgram *program;
			
			/** Imports an aiNode from assimp */
			void LoadNode(aiNode *node);
			/** Loads a bone from an aiNode */
			void LoadBones(aiNode *node, Bone *parent, Bone *new_bone);
			/** Updates a bone */
			
			/** Finds a bone by name given a parent node */
			Bone* FindBone(Bone *bone, const std::string &name);
			/** Gets a bone by name */
			inline Bone* GetBone(const std::string &name) {
				return FindBone(root_bone, name);
			}
			void UpdateBone(Bone *bone);
			
			/** Prints a bone heirarchy */
			inline void PrintBoneHierarchy(Bone *bone, int depth = 0) {
				for (int i = 0; i < depth; ++i) printf("\t");
				printf("%s\n", bone->name.c_str());
				for (auto pair : bone->children) {
					PrintBoneHierarchy(pair.second, depth + 1);
				}
			}
			
		public:
			SkinnedMesh(const std::string &name);
			~SkinnedMesh();
			
			/** Returns the shader program */
			inline ShaderProgram* GetShaderProgram() {
				return program;
			}
			/** Returns this mesh's base */
			inline SkinnedMeshBase* GetBase() {
				return base;
			}
			
			/** Loads a mesh from a file */
			bool LoadMesh(const std::string &file);
			/** Renders the mesh using the given camera */
			void Render(Camera *camera);
			
			
			/** Sets the correction matrix */
			inline void SetCorrectionMatrix(const FMat4 &correction_matrix) {
				this->correction_matrix = correction_matrix;
			}
			/** Sets the scale matrix */
			inline void SetScaleMatrix(const FMat4 &scale_matrix) {
				this->scale_matrix = scale_matrix;
			}
			/** Sets the model matrix */
			inline void SetModelMatrix(const FMat4 &model_matrix) {
				this->model_matrix = model_matrix;
			}
			/** Returns the correction matrix */
			inline const FMat4& GetCorrectionMatrix() const {
				return correction_matrix;
			}
			/** Returns the model matrix */
			inline const FMat4& GetModelMatrix() const {
				return model_matrix;
			}
			
			/** Returns the euler angles between two bones */
			FVec3 GetBoneAngle(Bone *a, Bone *b);
			/** Returns the bone final transforms */
			inline const std::vector<FMat4>& GetBoneFinalTransforms() const {
				return bone_final_transforms;
			}
			
			
			/** Applies a transformation to the given bone */
			void ApplyBoneTransform(const std::string &bone_name, const FMat4 &transformation);
			/** Sets the transformation of a given bone */
			void SetBoneTransform(const std::string &bone_name, const FMat4 &transform);
			/** Returns the final transform of a bone */
			inline FMat4 GetBoneFinalTransform(const std::string &bone_name) {
				Bone *bone = GetBone(bone_name);
				if ( bone == nullptr )
					return FMat4();
				else
					return bone->final_transform;
			}
			/** Returns the local transform of a bone */
			inline FMat4 GetBoneLocalTransform(const std::string &bone_name) {
				Bone *bone = GetBone(bone_name);
				if ( bone == nullptr )
					return FMat4();
				else
					return bone->local_transform;
			}
			/** Returns the global transform of a bone */
			inline FMat4 GetBoneGlobalTransform(const std::string &bone_name) {
				Bone *bone = GetBone(bone_name);
				if ( bone == nullptr )
					return FMat4();
				else
					return bone->global_transform;
			}
			
			/** Recalculates the transforms of each bone */
			void UpdateSkeleton();
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
	}
}

#endif /* SkinnedMesh_hpp */
