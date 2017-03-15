//
//  PhysicsObject.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/5/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "RigidBody.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix;
using namespace phoenix::scene;






RigidBody::RigidBody(CollisionShape *shape, float mass) {
	
	// Create a default motion state
	motion_state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	
	// Create a new rigid body
	btRigidBody::btRigidBodyConstructionInfo rigid_body_ci(mass, motion_state, shape->GetShape(), shape->CalculateLocalInertia(mass));
	rigid_body = new btRigidBody(rigid_body_ci);
	rigid_body->setActivationState(DISABLE_DEACTIVATION);
}
RigidBody::~RigidBody() {
	delete rigid_body;
	delete motion_state;
}






void RigidBody::Wrap(scripting::Script *script) {
	
	CollisionShape::Wrap(script);
	
	script->GetGlobalNamespace()
	.beginClass<RigidBody>("RigidBody")
	.addConstructor<void (*) (CollisionShape*, float)>()
	.addFunction("SetLinearVelocity", &RigidBody::SetLinearVelocity)
	.addFunction("GetLinearVelocity", &RigidBody::GetLinearVelocity)
	.addFunction("SetDamping", &RigidBody::SetDamping)
	.addFunction("GetPosition", &RigidBody::GetPosition)
	.addFunction("ApplyForce", &RigidBody::ApplyForce)
	.addFunction("SetPosition", &RigidBody::SetPosition)
	.addFunction("SetKinematic", &RigidBody::SetKinematic)
	.addFunction("SetAngularFactor", &RigidBody::SetAngularFactor)
	.endClass();
	
	
}


