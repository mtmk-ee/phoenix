//
//  Vector.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Vector.hpp"
#include "../Scripting/Script.hpp"







void phoenix::WrapVectors(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<IVec2>("IVec2")
	.addConstructor<void(*)(int, int)>()
	.addData("x", &IVec2::x)
	.addData("y", &IVec2::y)
	.endClass()
	
	.beginClass<IVec3>("IVec3")
	.addConstructor<void(*)(int, int, int)>()
	.addData("x", &IVec3::x)
	.addData("y", &IVec3::y)
	.addData("z", &IVec3::z)
	.endClass()
	
	.beginClass<IVec4>("IVec4")
	.addConstructor<void(*)(int, int, int, int)>()
	.addData("x", &IVec4::x)
	.addData("y", &IVec4::y)
	.addData("z", &IVec4::z)
	.addData("w", &IVec4::w)
	.endClass()
	
	.beginClass<FVec2>("FVec2")
	.addConstructor<void(*)(float, float)>()
	.addData("x", &FVec2::x)
	.addData("y", &FVec2::y)
	.endClass()
	
	.beginClass<FVec3>("FVec3")
	.addConstructor<void(*)(float, float, float)>()
	.addData("x", &FVec3::x)
	.addData("y", &FVec3::y)
	.addData("z", &FVec3::z)
	.endClass()
	
	.beginClass<FVec4>("FVec4")
	.addConstructor<void(*)(float, float, float, float)>()
	.addData("x", &FVec4::x)
	.addData("y", &FVec4::y)
	.addData("z", &FVec4::z)
	.addData("w", &FVec4::w)
	.endClass()
	
	
	
	.beginNamespace("Vector")
	.addFunction("AddFVec2", VectorAdd<FVec2>)
	.addFunction("SubFVec2", VectorSub<FVec2>)
	.addFunction("MultFVec2", VectorMult<FVec2>)
	.addFunction("DivFVec2", VectorDiv<FVec2>)
	.addFunction("NormalizeFVec2", VectorNormalize<FVec2>)
	.addFunction("LengthFVec2", VectorLength<FVec2>)
	
	.addFunction("AddFVec3", VectorAdd<FVec3>)
	.addFunction("SubFVec3", VectorSub<FVec3>)
	.addFunction("MultFVec3", VectorMult<FVec3>)
	.addFunction("DivFVec3", VectorDiv<FVec3>)
	.addFunction("NormalizeFVec3", VectorNormalize<FVec3>)
	.addFunction("LengthFVec3", VectorLength<FVec3>)
	
	.addFunction("AddFVec4", VectorAdd<FVec4>)
	.addFunction("SubFVec4", VectorSub<FVec4>)
	.addFunction("MultFVec4", VectorMult<FVec4>)
	.addFunction("DivFVec4", VectorDiv<FVec4>)
	.addFunction("NormalizeFVec4", VectorNormalize<FVec4>)
	.addFunction("LengthFVec4", VectorLength<FVec4>)
	
	.addFunction("FVec3ToFVec4", VectorFVec3ToFVec4)
	.addFunction("FVec4ToFVec3", VectorFVec4ToFVec3)
	
	.addFunction("CopyFVec3", VectorCopy<FVec3>)
	.addFunction("CopyFVec4", VectorCopy<FVec4>);
	
	
	
	
}








