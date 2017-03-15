//
//  Camera.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp


#include "../Util/Matrix.hpp"

namespace phoenix {
	namespace video {
		class ShaderProgram;
		
		
		struct PerspectiveProjectionInfo
		{
			float FOV;
			float aspect;
			float zNear;
			float zFar;
		};
		
		
		struct OrthoProjectionInfo {
			float r;
			float l;
			float b;
			float t;
			float n;
			float f;
		};
		
		
		
		/** A camera class which calculates view and projection matrices for use by shader programs */
		class Camera {
		protected:
			const float MAX_X_ROTATION = 87.0f;
			FVec3 position, rotation;
			FMat4 orientation, view_matrix, projection_matrix, vp_matrix;
			
			void NormalizeAngles();
			void CalculateOrientation();
			void CalculateMatrices();
			
		public:
			Camera();
			virtual ~Camera() {
				
			}
			
			/** Translates the camera by the given offset */
			void Translate(const FVec3 &offset) {
				position += offset;
			}
			/** Rotates the camera by the given euler angle offset */
			void Rotate(const FVec3 &offset) {
				rotation += offset;
				NormalizeAngles();
			}
			
			
			/** Returns the orientation matrix */
			inline FMat4 GetOrientationMatrix() const {
				return orientation;
			}
			/** Returns the view matrix */
			inline FMat4 GetViewMatrix() const {
				return view_matrix;
			}
			/** Returns the projection matrix */
			inline FMat4 GetProjectionMatrix() const {
				return projection_matrix;
			}
			/** Returns the View matrix * Projection Matrix */
			inline FMat4 GetVPMatrix() const {
				return vp_matrix;
			}
			
			
			/** Returns the camera's position */
			inline FVec3 GetPosition() const {
				return position;
			}
			/** Returns the camera's rotation */
			inline FVec3 GetRotation() const {
				return rotation;
			}
			
			/** Sets the camera's position */
			inline void SetPosition(const FVec3 &position) {
				this->position = position;
			}
			/** Sets the camera's rotation */
			inline void SetRotation(const FVec3 &rotation) {
				this->rotation = rotation;
			}
			
			
			
			/** Returns a vector describing where the camera is looking at */
			inline FVec3 GetForwardVector() const {
				return glm::vec3(glm::inverse(GetOrientationMatrix()) * glm::vec4(0, 0, -1, 1));
			}
			/** Returns a vector pointing the opposite direction of the forward vector */
			inline FVec3 GetBackwardVector() const {
				return -GetForwardVector();
			}
			/** Returns a vector pointing to the right of the forward vector */
			inline FVec3 GetRightVector() const {
				return glm::vec3(glm::inverse(GetOrientationMatrix()) * glm::vec4(1, 0, 0, 1));
			}
			/** Returns a vector pointing to the left of the forward vector */
			inline FVec3 GetLeftVector() const {
				return -GetRightVector();
			}
			/** Returns a vector pointing above the camera */
			inline FVec3 GetUpVector() const {
				return glm::vec3(glm::inverse(GetOrientationMatrix()) * glm::vec4(0, 1, 0, 1));
			}
			/** Returns a vector pointing below the camera */
			inline FVec3 GetDownVector() const {
				return -GetUpVector();
			}
			
			
			
			
			
			/** Updates the camera (recalculates matrices) */
			void Update();
			/** Updates a shader program's uniforms */
			void UpdateProgram(ShaderProgram *program, const FMat4 &model_matrix);
			
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
		class PerspectiveCamera : public Camera {
			const float MAX_X_ROTATION = 87.0f;
			float aspect_ratio, fov;
			float near_z, far_z;
			
		public:
			PerspectiveCamera(float aspect_ratio, float fov, float near_z, float far_z);
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		class OrthoCamera : public Camera {
			float left;
			float right;
			float bottom;
			float top;
			float near_z;
			float far_z;
			
		public:
			OrthoCamera(float left, float right, float bottom, float top, float near_z, float far_z);
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
	}
}

#endif /* Camera_hpp */
