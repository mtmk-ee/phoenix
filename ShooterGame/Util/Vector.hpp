//
//  Vector.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <glm/glm.hpp>
#include <Bullet/btBulletDynamicsCommon.h>

namespace phoenix {
	namespace scripting { class Script; }
	
	
	
	// Vector typedefs
	typedef glm::ivec2 IVec2;
	typedef glm::fvec2 FVec2;
	typedef glm::dvec2 DVec2;
	typedef glm::ivec3 IVec3;
	typedef glm::fvec3 FVec3;
	typedef glm::dvec3 DVec3;
	typedef glm::ivec4 IVec4;
	typedef glm::fvec4 FVec4;
	typedef glm::dvec4 DVec4;
	
	
	void WrapVectors(scripting::Script *script);
	
	/* Template vector functions */
	template <typename T>
	inline T VectorAdd(const T &a, const T &b) {
		return a + b;
	}
	template <typename T>
	inline T VectorSub(const T &a, const T &b) {
		return a - b;
	}
	template <typename T>
	inline T VectorMult(const T &a, float scalar) {
		return a * scalar;
	}
	template <typename T>
	inline T VectorDiv(const T &a, float scalar) {
		if ( scalar == 0 ) return T();
		else return a / scalar;
	}
	template <typename T>
	inline float VectorLength(const T &a) {
		return glm::length(a);
	}
	template <typename T>
	inline T VectorNormalize(const T &a) {
		if ( VectorLength(a) == 0 ) return T();
		else return glm::normalize(a);
	}
	inline FVec4 VectorFVec3ToFVec4(const FVec3 &vec) {
		return FVec4(vec.x, vec.y, vec.z, 1);
	}
	inline FVec3 VectorFVec4ToFVec3(const FVec4 &vec) {
		return FVec3(vec.x, vec.y, vec.z);
	}
	template <typename T>
	inline T VectorCopy(const T &vec) {
		return vec;
	}
	
	
	/** Converts an FVec3 to a btVector3 */
	inline btVector3 VectorGLMToBullet(const FVec3 &vec) {
		return btVector3(vec.x, vec.y, vec.z);
	}
	/** Converts a btVector3 to an FVec3 */
	inline FVec3 VectorBulletToGLM(const btVector3 &vec) {
		return FVec3(vec.x(), vec.y(), vec.z());
	}
	
	
	
	
	// Angle unit conversions
	inline float ToRadians(float degrees) {
		return glm::radians(degrees);
	}
	inline float ToDegrees(float radians) {
		return glm::degrees(radians);
	}
	
	
}

#endif /* Vector_hpp */
