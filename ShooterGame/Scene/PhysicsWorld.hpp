//
//  PhysicsWorld.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/3/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef PhysicsWorld_hpp
#define PhysicsWorld_hpp

#include "../Util/Time.hpp"
#include "RigidBody.hpp"
#include "CollisionObject.hpp"
#include "DebugDrawer.hpp"
#include "../Video/Camera.hpp"

namespace phoenix {
	namespace scene {
		
		
		
		/** Handles physics in a game */
		class PhysicsWorld {
			btBroadphaseInterface *broadphase;
			btDefaultCollisionConfiguration *collision_config;
			btCollisionDispatcher *dispatcher;
			btSequentialImpulseConstraintSolver *solver;
			btDiscreteDynamicsWorld *dynamics_world;
			DebugDrawer *drawer;
			
			Duration time_since_last_update;
			int update_rate;
			
			std::vector<RigidBody*> rigid_bodies;
			
		public:
			PhysicsWorld();
			~PhysicsWorld();
			
			
			/** Sets the rate the world is updated at (updates/sec) */
			inline void SetUpdateRate(int rate) {
				update_rate = rate;
			}
			/** Returns the rate the world is updated at */
			inline int GetUpdateRate() const {
				return update_rate;
			}
			
			/** Sets the gravity of the world */
			inline void SetGravity(const FVec3 &gravity) {
				dynamics_world->setGravity(VectorGLMToBullet(gravity));
			}
			/** Returns the gravity of the world */
			inline FVec3 GetGravity() const {
				return VectorBulletToGLM(dynamics_world->getGravity());
			}
			
			
			/** Steps the physics world simulation by the given amount of time */
			void StepWorld(const Duration &delta_time);
			/** Debug draws the world */
			inline void Render(video::Camera *camera) {
				drawer->SetMatrices(camera->GetViewMatrix(), camera->GetProjectionMatrix());
				dynamics_world->debugDrawWorld();
			}
			
			/** Performs a simple raycast test from a given point, to a given point */
			bool SimpleRaycast(const FVec3 &from, const FVec3 &to);
			
			
			/** Adds a rigid body to the world */
			void AddRigidBody(RigidBody *rigid_body);
			/** Adds a collision object */
			void AddCollisionObject(CollisionObject *object);
			
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
	}
}

#endif /* PhysicsWorld_hpp */
