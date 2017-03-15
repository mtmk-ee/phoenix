//
//  CollisionObject.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/6/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef CollisionObject_hpp
#define CollisionObject_hpp

#include "CollisionShape.hpp"

namespace phoenix {
	namespace scene {
		
		
		
		/** A static collision object */
		class CollisionObject {
			CollisionShape *shape;
			btCollisionObject *object;
			
		public:
			CollisionObject(CollisionShape *shape);
			
			/** Returns the internal btCollisionObject instance */
			inline btCollisionObject* GetObject() {
				return object;
			}
			
			/** Used for triangle meshes */
			inline void SetCustomMaterialFlag() {
				object->setCollisionFlags(object->getCollisionFlags()|btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
			}
			/** Sets the friction */
			inline void SetFriction(float friction) {
				object->setFriction(friction);
			}
			/** Sets the position */
			inline void SetPosition(const FVec3 &position) {
				btTransform transform = object->getWorldTransform();
				transform.setOrigin(VectorGLMToBullet(position));
				object->setWorldTransform(transform);
			}
			
			static void Wrap(scripting::Script *script);
			
			
		};
		
		
		
		
	}
}

#endif /* CollisionObject_hpp */
