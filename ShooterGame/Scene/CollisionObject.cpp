//
//  CollisionObject.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/6/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "CollisionObject.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix::scene;


CollisionObject::CollisionObject(CollisionShape *shape) : shape(shape), object(new btCollisionObject()) {
	object->setCollisionShape(shape->GetShape());
}


void CollisionObject::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<CollisionObject>("CollisionObject")
	.addConstructor<void (*) (CollisionShape*)>()
	.addFunction("SetCustomMaterialFlag", &CollisionObject::SetCustomMaterialFlag)
	.addFunction("SetFriction", &CollisionObject::SetFriction)
	.addFunction("SetPosition", &CollisionObject::SetPosition)
	.endClass();
}










