//
//  Lighting.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/22/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Lighting_hpp
#define Lighting_hpp

#include "../Util/Vector.hpp"

namespace phoenix {
	namespace video {
		
		
		struct BaseLight
		{
			FVec3 Color;
			float AmbientIntensity;
			float DiffuseIntensity;
			
			BaseLight()
			{
				Color = FVec3(0.0f, 0.0f, 0.0f);
				AmbientIntensity = 0.0f;
				DiffuseIntensity = 0.0f;
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		struct DirectionalLight : public BaseLight
		{
			FVec3 Direction;
			
			DirectionalLight()
			{
				Direction = FVec3(0.0f, 0.0f, 0.0f);
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		struct PointLight : public BaseLight
		{
			FVec3 Position;
			
			struct Att {
				float Constant;
				float Linear;
				float Exp;
			} Attenuation;
			
			PointLight()
			{
				Position = FVec3(0.0f, 0.0f, 0.0f);
				Attenuation.Constant = 1.0f;
				Attenuation.Linear = 0.0f;
				Attenuation.Exp = 0.0f;
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		struct SpotLight : public PointLight
		{
			FVec3 Direction;
			float Cutoff;
			
			SpotLight()
			{
				Direction = FVec3(0.0f, 0.0f, 0.0f);
				Cutoff = 0.0f;
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		
	}
}

#endif /* Lighting_hpp */
