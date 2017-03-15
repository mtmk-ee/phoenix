//
//  Matrix.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vector.hpp"


namespace phoenix {
	namespace scripting { class Script; }
	
	
	// Matrix Typedefs
	typedef glm::fmat2 FMat2;
	typedef glm::fmat3 FMat3;
	typedef glm::fmat4 FMat4;
	
	/** Removes translation from a matrix */
	inline FMat4 MatrixRemoveTranslation(const FMat4 &transform) {
		return FMat4(FMat3(transform));
	}
	
	/** Multiplies two matrices */
	template <typename T>
	inline T MatrixMultiply(const T &a, const T &b) {
		return a * b;
	}
	/** Multiplies two matrices */
	template <typename T, typename U>
	inline U MatrixMultiply(const T &a, const U &b) {
		return a * b;
	}
	template <typename T>
	inline T MatrixInverse(const T &mat) {
		return glm::inverse(mat);
	}
	/** Applies a rotation transformation to a matrix */
	inline FMat4 MatrixRotate(const FMat4 &matrix, float angle, const FVec3 &axis) {
		return glm::rotate(matrix, angle, axis);
	}
	/** Applies a linear translation to a matrix */
	inline FMat4 MatrixTranslate(const FMat4 &matrix, const FVec3 &translation) {
		return glm::translate(matrix, translation);
	}
	/** Returns the determinant of the matrix */
	inline float MatrixDeterminant(const FMat2 &matrix) {
		return glm::determinant(matrix);
	}
	/** Returns the determinant of the matrix */
	inline float MatrixDeterminant(const FMat3 &matrix) {
		return glm::determinant(matrix);
	}
	/** Returns the determinant of the matrix */
	inline float MatrixDeterminant(const FMat4 &matrix) {
		return glm::determinant(matrix);
	}
	/** Sets the given matrix to the zero matrix */
	inline void MatrixSetZero(FMat4 &matrix) {
		float mat[16] = {0};
		matrix = glm::make_mat4(mat);
	}
	/** Constructs a 4x4 matrix from a 3x3 matrix */
	inline FMat4 MatrixFMat4ToFMat3(const FMat3 &matrix3) {
		FMat4 matrix4;
		for (int r = 0; r < 3; ++r) {
			for (int c = 0; c < 3; ++ c) {
				matrix4[r][c] = matrix3[r][c];
			}
		}
		
		return matrix4;
	}
	
	
	/** Creates a scale transform */
	FMat4 MatrixCreateScaleTransform(const FVec3 &scale);
	/** Creates a rotation transform given three euler angles */
	FMat4 MatrixCreateRotationTransform(const FVec3 &rotation);
	/** Creates a translation transform */
	FMat4 MatrixCreateTranslationTransform(const FVec3 &translation);
	
	
	void WrapMatrices(scripting::Script *script);
	
	
}

#endif /* Matrix_hpp */
