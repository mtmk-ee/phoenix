//
//  Matrix.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Matrix.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix;

FMat4 phoenix::MatrixCreateScaleTransform(const FVec3 &scale) {
	FMat4 scale_matrix(1.0f);
	
	// Set scale values along the diagonal
	scale_matrix[0][0] = scale.x;
	scale_matrix[1][1] = scale.y;
	scale_matrix[2][2] = scale.z;
	
	// Return the scale matrix
	return scale_matrix;
}
FMat4 phoenix::MatrixCreateRotationTransform(const FVec3 &rotation) {
	
	// Create a matrix for rotation around each axis
	FMat4 rx, ry, rz;
	
	// Convert angles to radians
	float x = ToRadians(rotation.x);
	float y = ToRadians(rotation.y);
	float z = ToRadians(rotation.z);
	
	// X-axis rotation matrix
	rx[0][0] = 1.0f; rx[0][1] = 0.0f   ; rx[0][2] = 0.0f    ; rx[0][3] = 0.0f;
	rx[1][0] = 0.0f; rx[1][1] = cosf(x); rx[1][2] = -sinf(x); rx[1][3] = 0.0f;
	rx[2][0] = 0.0f; rx[2][1] = sinf(x); rx[2][2] = cosf(x) ; rx[2][3] = 0.0f;
	rx[3][0] = 0.0f; rx[3][1] = 0.0f   ; rx[3][2] = 0.0f    ; rx[3][3] = 1.0f;
	
	// Y-axis rotation matrix
	ry[0][0] = cosf(y); ry[0][1] = 0.0f; ry[0][2] = -sinf(y); ry[0][3] = 0.0f;
	ry[1][0] = 0.0f   ; ry[1][1] = 1.0f; ry[1][2] = 0.0f    ; ry[1][3] = 0.0f;
	ry[2][0] = sinf(y); ry[2][1] = 0.0f; ry[2][2] = cosf(y) ; ry[2][3] = 0.0f;
	ry[3][0] = 0.0f   ; ry[3][1] = 0.0f; ry[3][2] = 0.0f    ; ry[3][3] = 1.0f;
	
	// Z-axis rotation matrix
	rz[0][0] = cosf(z); rz[0][1] = -sinf(z); rz[0][2] = 0.0f; rz[0][3] = 0.0f;
	rz[1][0] = sinf(z); rz[1][1] = cosf(z) ; rz[1][2] = 0.0f; rz[1][3] = 0.0f;
	rz[2][0] = 0.0f   ; rz[2][1] = 0.0f    ; rz[2][2] = 1.0f; rz[2][3] = 0.0f;
	rz[3][0] = 0.0f   ; rz[3][1] = 0.0f    ; rz[3][2] = 0.0f; rz[3][3] = 1.0f;
	
	// Combine the rotations and return the result
	return rx * ry * rz;
}
FMat4 phoenix::MatrixCreateTranslationTransform(const FVec3 &translation) {
	FMat4 translation_matrix;
	
	// Set the last column in the matrix to the translation
	translation_matrix[3][0]  = translation.x;
	translation_matrix[3][1]  = translation.y;
	translation_matrix[3][2]  = translation.z;
	
	// Return the translation matrix
	return translation_matrix;
}




void phoenix::WrapMatrices(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<FMat2>("FMat2")
	.addConstructor<void (*) (float)>()
	.endClass()
	
	.beginClass<FMat3>("FMat3")
	.addConstructor<void (*) (float)>()
	.endClass()
	
	.beginClass<FMat4>("FMat4")
	.addConstructor<void (*) (float)>()
	.endClass()
	
	.beginNamespace("Matrix")
	.addFunction("RemoveTranslation", MatrixRemoveTranslation)
	.addFunction("MultiplyFMat3", MatrixMultiply<FMat3>)
	.addFunction("MultiplyFMat4", MatrixMultiply<FMat4>)
	.addFunction("MultiplyFMat4FVec4", MatrixMultiply<FMat4, FVec4>)
	.addFunction("InverseFMat3", MatrixInverse<FMat3>)
	.addFunction("InverseFMat4", MatrixInverse<FMat4>)
	.addFunction("Rotate", MatrixRotate)
	.addFunction("Translate", MatrixTranslate)
	.addFunction("CreateRotationTransform", MatrixCreateRotationTransform)
	.addFunction("CreateTranslationTransform", MatrixCreateTranslationTransform)
	.addFunction("CreateScaleTransform", MatrixCreateScaleTransform)
	.endNamespace();
}






