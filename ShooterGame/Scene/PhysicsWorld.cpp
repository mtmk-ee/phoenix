//
//  PhysicsWorld.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/3/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "PhysicsWorld.hpp"
#include "../Scripting/Script.hpp"

using namespace phoenix;
using namespace phoenix::scene;







PhysicsWorld::PhysicsWorld() {
	// Create new world
	broadphase = new btDbvtBroadphase();
	collision_config = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_config);
	solver = new btSequentialImpulseConstraintSolver();
	dynamics_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config);
	dynamics_world->setDebugDrawer(drawer = new DebugDrawer());
	
	// Set defaults of the world
	SetGravity(FVec3(0, -9.81, 0));
	SetUpdateRate(60);
}
PhysicsWorld::~PhysicsWorld() {
	delete dynamics_world;
	delete solver;
	delete dispatcher;
	delete collision_config;
	delete broadphase;
	delete drawer;
}


void PhysicsWorld::StepWorld(const Duration &delta_time) {
	time_since_last_update += delta_time;
	if ( time_since_last_update.Seconds() >= (1.0 / update_rate) ) {
		dynamics_world->stepSimulation(time_since_last_update.Seconds());
		time_since_last_update = Duration::Zero();
	}
}


bool PhysicsWorld::SimpleRaycast(const FVec3 &from, const FVec3 &to) {
	btVector3 bt_from = VectorGLMToBullet(from);
	btVector3 bt_to = VectorGLMToBullet(to);
	btCollisionWorld::ClosestRayResultCallback res(bt_from, bt_to);
	
	// Raycast in the world
	dynamics_world->rayTest(bt_from, bt_to, res);
	return res.hasHit();
}


void PhysicsWorld::AddRigidBody(phoenix::scene::RigidBody *rigid_body) {
	rigid_bodies.push_back(rigid_body);
	dynamics_world->addRigidBody(rigid_body->GetRigidBody());
}
void PhysicsWorld::AddCollisionObject(phoenix::scene::CollisionObject *object) {
	dynamics_world->addCollisionObject(object->GetObject());
}




void PhysicsWorld::Wrap(scripting::Script *script) {
	RigidBody::Wrap(script);
	CollisionObject::Wrap(script);
	
	script->GetGlobalNamespace()
	.beginClass<PhysicsWorld>("PhysicsWorld")
	.addFunction("SetUpdateRate", &PhysicsWorld::SetUpdateRate)
	.addFunction("GetUpdateRate", &PhysicsWorld::GetUpdateRate)
	.addFunction("SetGravity", &PhysicsWorld::SetGravity)
	.addFunction("GetGravity", &PhysicsWorld::GetGravity)
	.addFunction("AddRigidBody", &PhysicsWorld::AddRigidBody)
	.addFunction("AddCollisionObject", &PhysicsWorld::AddCollisionObject)
	.addFunction("SimpleRaycast", &PhysicsWorld::SimpleRaycast)
	.addFunction("Render", &PhysicsWorld::Render)
	.endClass();
}










