//
//  Lighting.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/22/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Lighting.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix::video;





void BaseLight::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<BaseLight>("DirectionalLight")
	.addConstructor<void (*)()>()
	.addData("color", &BaseLight::Color)
	.addData("ambient_intensity", &BaseLight::AmbientIntensity)
	.addData("diffuse_intensity", &BaseLight::DiffuseIntensity)
	.endClass();
	
	DirectionalLight::Wrap(script);
	PointLight::Wrap(script);
	SpotLight::Wrap(script);
}

void DirectionalLight::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<DirectionalLight, BaseLight>("DirectionalLight")
	.addConstructor<void (*)()>()
	.addData("direction", &DirectionalLight::Direction)
	.endClass();
}

void PointLight::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<Att>("Attenuation")
	.addData("constant", &Att::Constant)
	.addData("linear", &Att::Linear)
	.addData("exp", &Att::Exp)
	.endClass()
	
	.deriveClass<PointLight, BaseLight>("PointLight")
	.addConstructor<void (*)()>()
	.addData("position", &PointLight::Position)
	.addData("attenuation", &PointLight::Attenuation)
	.endClass();
}

void SpotLight::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.deriveClass<SpotLight, BaseLight>("SpotLight")
	.addConstructor<void (*)()>()
	.addData("direction", &SpotLight::Direction)
	.addData("cutoff", &SpotLight::Cutoff)
	.endClass();
}





