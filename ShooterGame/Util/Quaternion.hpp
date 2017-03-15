//
//  Quaternion.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/7/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "Vector.hpp"
#include <glm/gtc/quaternion.hpp>

namespace phoenix {
	
	typedef glm::fquat Quaternion;
	
	
	inline Quaternion QuaternionFromEuler(const FVec3 &euler) {
		const float PI_DIV_180 = M_PI / 180.0;
		return Quaternion(FVec3(euler.x * PI_DIV_180, euler.y * PI_DIV_180, euler.z * PI_DIV_180));
	}
	inline Quaternion QuaternionNormalize(const Quaternion &quat) {
		return glm::normalize(quat);
	}
	
	
	void WrapQuaternion(scripting::Script *script);
	
	
	
	
}

#endif /* Quaternion_hpp */
