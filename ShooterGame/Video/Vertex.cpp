//
//  VertexInfo.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/20/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Vertex.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix::video;











void Vertex::Wrap(scripting::Script *script) {
	
	script->GetGlobalNamespace()
	.beginClass<Vertex>("Vertex")
	.addData("vertex", &Vertex::vertex)
	.addData("normal", &Vertex::normal)
	.addData("uv", &Vertex::uv)
	.addConstructor<void (*) (const FVec3&, const FVec3&, const FVec2&)>()
	.endClass();
	
}



