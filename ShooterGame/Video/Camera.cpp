//
//  Camera.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Camera.hpp"
#include "Shader.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix::video;





Camera::Camera() : position(0, 0, 0), rotation(0, 0, 0) {
	CalculateMatrices();
}


void Camera::NormalizeAngles() {
	// Normalize rotation
	rotation.x = fmodf(rotation.x, 360);
	rotation.y = fmodf(rotation.y, 360);
	rotation.z = fmodf(rotation.z, 360);
	
	// Make sure the rotation doesn't go over or under the max rotation
	if ( rotation.x > MAX_X_ROTATION ) rotation.x = MAX_X_ROTATION;
	else if ( rotation.x < -MAX_X_ROTATION ) rotation.x = -MAX_X_ROTATION;
}
void Camera::CalculateOrientation() {
	glm::mat4 orientation(1.0f);
	
	// Rotate the matrix
	if ( rotation.x != 0 ) orientation = MatrixRotate(orientation, ToRadians(rotation.x), FVec3(1, 0, 0));
	if ( rotation.y != 0 ) orientation = MatrixRotate(orientation, ToRadians(rotation.y), FVec3(0, 1, 0));
	
	// Set the orientation
	this->orientation = orientation;
}
void Camera::CalculateMatrices() {
	CalculateOrientation();
	
	// Calculate matrices
	view_matrix = orientation * MatrixTranslate(glm::mat4(), -position);
	vp_matrix = projection_matrix * view_matrix;
}

void Camera::Update() {
	NormalizeAngles();
	CalculateMatrices();
}
void Camera::UpdateProgram(ShaderProgram *program, const FMat4 &model_matrix) {
	//program->SetMVPMatrix(vp_matrix * model_matrix);
	program->SetViewMatrix(view_matrix);
	program->SetModelMatrix(model_matrix);
	program->SetProjectionMatrix(projection_matrix);
	program->SetCameraPosition(position);
	program->SetUniformInt("sampler", 0);
}

PerspectiveCamera::PerspectiveCamera(float aspect_ratio, float fov, float near_z, float far_z)
: aspect_ratio(aspect_ratio), fov(fov), near_z(near_z), far_z(far_z) {
	projection_matrix = glm::perspective(45.0f, aspect_ratio, near_z, far_z);
}



OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near_z, float far_z)
: left(left), right(right), bottom(bottom), top(top), near_z(near_z), far_z(far_z) {
	projection_matrix = glm::ortho(left, right, bottom, top, near_z, far_z);
}


void Camera::Wrap(scripting::Script *script) {
	
	
	
	script->GetGlobalNamespace()
	.beginClass<Camera>("Camera")
	.addFunction("Translate", &Camera::Translate)
	.addFunction("Rotate", &Camera::Rotate)
	.addFunction("GetOrientationMatrix", &Camera::GetOrientationMatrix)
	.addFunction("GetViewMatrix", &Camera::GetViewMatrix)
	.addFunction("GetProjectionMatrix", &Camera::GetProjectionMatrix)
	.addFunction("GetVPMatrix", &Camera::GetVPMatrix)
	.addFunction("GetPosition", &Camera::GetPosition)
	.addFunction("GetRotation", &Camera::GetRotation)
	.addFunction("SetPosition", &Camera::SetPosition)
	.addFunction("SetRotation", &Camera::SetRotation)
	.addFunction("GetForwardVector", &Camera::GetForwardVector)
	.addFunction("GetBackwardVector", &Camera::GetBackwardVector)
	.addFunction("GetRightVector", &Camera::GetRightVector)
	.addFunction("GetLeftVector", &Camera::GetLeftVector)
	.addFunction("GetUpVector", &Camera::GetUpVector)
	.addFunction("GetDownVector", &Camera::GetDownVector)
	.addFunction("Update", &Camera::Update)
	.addFunction("UpdateProgram", &Camera::UpdateProgram)
	.endClass();
	
	PerspectiveCamera::Wrap(script);
	OrthoCamera::Wrap(script);
	
}

void PerspectiveCamera::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<PerspectiveCamera, Camera>("PerspectiveCamera")
	.addConstructor<void (*) (float, float, float, float)>()
	.endClass();
}

void OrthoCamera::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<OrthoCamera, Camera>("OrthoCamera")
	.addConstructor<void (*) (float, float, float, float, float, float)>()
	.endClass();
}



