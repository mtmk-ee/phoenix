//
//  PhysicsObject.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/5/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef PhysicsObject_hpp
#define PhysicsObject_hpp

#include "CollisionShape.hpp"



namespace phoenix {
	namespace scene {
		
		
		/** A rigid body you can add to a physics world */
		class RigidBody {
			btRigidBody *rigid_body;
			btDefaultMotionState *motion_state;
			
			
		public:
			RigidBody(CollisionShape *shape, float mass);
			~RigidBody();
			
			
			/** Returns the btRigidBody held by this class */
			inline btRigidBody* GetRigidBody() {
				return rigid_body;
			}
			/** Sets the linear velocity of this rigid body */
			inline void SetLinearVelocity(const FVec3 &velocity) {
				rigid_body->setLinearVelocity(VectorGLMToBullet(velocity));
			}
			/** Applies a force to this rigid body */
			inline void ApplyForce(const FVec3 &force) {
				rigid_body->applyImpulse(VectorGLMToBullet(force), btVector3(0, 0, 0));
			}
			/** Sets the damping of the rigid body */
			inline void SetDamping(float linear, float angular) {
				rigid_body->setDamping(linear, angular);
			}
			/** Sets the angular factor */
			inline void SetAngularFactor(const FVec3 &factor) {
				rigid_body->setAngularFactor(VectorGLMToBullet(factor));
			}
			/** Returns the center of mass */
			inline FVec3 GetPosition() {
				return VectorBulletToGLM(rigid_body->getWorldTransform().getOrigin());
			}
			/** Sets the position of the rigid body */
			inline void SetPosition(const FVec3 &position) {
				btTransform transform = rigid_body->getWorldTransform();
				transform.setOrigin(VectorGLMToBullet(position));
				rigid_body->setWorldTransform(transform);
			}
			/** Makes the body kinematic */
			inline void SetKinematic() {
				rigid_body->setCollisionFlags(rigid_body->getCollisionFlags()|btCollisionObject::CF_KINEMATIC_OBJECT);
			}
			/** Returns the linear velocity */
			inline FVec3 GetLinearVelocity() {
				return VectorBulletToGLM(rigid_body->getLinearVelocity()) ;
			}
			
			
			
			static void Wrap(scripting::Script *script);
			
		};
		
		
		
		
		
		
		
	}
}

#endif /* PhysicsObject_hpp */
