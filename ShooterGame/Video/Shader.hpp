//
//  Shader.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/12/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include "../Util/Matrix.hpp"

namespace phoenix {
	namespace scripting { class Script; }
	
	
	namespace video {
		
		
		
		/** Shader type */
		enum ShaderType {
			PHOENIX_SHADER_VERTEX,
			PHOENIX_SHADER_FRAGMENT,
		};
		
		
		/** A source object for a shader program */
		class ShaderSource {
			unsigned int source_id;
			
			
			inline ShaderSource(unsigned int source_id) : source_id(source_id) { }
			
		public:
			~ShaderSource();
			
			/** Loads a shader from a file */
			static ShaderSource* Load(const std::string &file, int shader_type);
			/** Loads a shader from a string */
			static ShaderSource* New(const std::string &shader_source, int shader_type);
			/** Deletes a shader source */
			static inline void Delete(ShaderSource *source) {
				delete source;
			}
			
			/** Returns the ID */
			inline unsigned int GetID() const {
				return source_id;
			}
			
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
		/** A shader program */
		class ShaderProgram {
			unsigned int program_id;
			bool created;
			
		public:
			ShaderProgram();
			~ShaderProgram();
			
			static inline ShaderProgram* New() {
				return new ShaderProgram();
			}
			
			inline void LoadSource(const std::string &path, int type) {
				ShaderSource *source = ShaderSource::Load(path, (ShaderType)type);
				AttachShader(source);
				delete source;
			}
			
			
			/** Checks if the program has been linked yet */
			inline bool IsLinked() const {
				return created;
			}
			
			/** Attachs a shader source */
			void AttachShader(ShaderSource *source);
			/** Links the shader program */
			bool LinkProgram();
			/** Uses the shader program */
			void UseProgram();
			/** Stops using the shader program */
			void UnbindProgram();
			
			
			/** Sets the model matrix uniform */
			void SetModelMatrix(const FMat4 &model_matrix) {
				SetUniformFMat4("model", model_matrix);
			}
			/** Sets the view matrix uniform */
			void SetViewMatrix(const FMat4 &view_matrix) {
				SetUniformFMat4("view", view_matrix);
			}
			/** Sets the projection matrix */
			void SetProjectionMatrix(const FMat4 &projection_matrix) {
				SetUniformFMat4("projection", projection_matrix);
			}
			/** Sets the model-view-projection matrix uniform */
			void SetMVPMatrix(const FMat4 &mvp_matrix) {
				SetUniformFMat4("mvp", mvp_matrix);
			}
			/** Sets the camera position uniform */
			void SetCameraPosition(const FVec3 &position) {
				SetUniformFVec3("camera", position);
			}
			
			
			static void Wrap(scripting::Script *script);
			
			
			
			/* Set Uniforms */
			void SetUniform(const std::string &name, float* values, int count);
			void SetUniformFloat(const std::string &name, const float value);
			void SetUniform(const std::string &name, FVec2* vectors, int count);
			void SetUniformFVec2(const std::string &name, const FVec2 &vector);
			void SetUniform(const std::string &name, FVec3* vectors, int count);
			void SetUniformFVec3(const std::string &name, const FVec3 &vector);
			void SetUniform(const std::string &name, FVec4* vectors, int count);
			void SetUniformFVec4(const std::string &name, const FVec4 &vector);
			void SetUniform(const std::string &name, FMat3* matrices, int count);
			void SetUniformFMat3(const std::string &name, const FMat3 &matrix);
			void SetUniform(const std::string &name, FMat4* matrices, int count);
			void SetUniformFMat4(const std::string &name, const FMat4 &matrix);
			void SetUniform(const std::string &name, int* values, int count);
			void SetUniformInt(const std::string &name, const int value);
		};
		
		
		
		
	}
}

#endif /* Shader_hpp */
