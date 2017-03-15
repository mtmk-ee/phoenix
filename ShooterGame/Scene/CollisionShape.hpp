//
//  CollisionShape.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/5/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef CollisionShape_hpp
#define CollisionShape_hpp

#include "../Video/SkinnedMesh.hpp"
#include "btBvhTriangleMeshShape.h"


namespace phoenix {
	namespace scene {
		
		
		
		
		/** Base collision shape. Don't use this class, use the derived classes */
		class CollisionShape {
		protected:
			btCollisionShape *shape;
			bool local_inertia_supported;
			
		public:
			CollisionShape(bool local_inertia_supported = true);
			CollisionShape(btCollisionShape *shape, bool local_inertia_supported = true);
			virtual ~CollisionShape();
			
			
			inline btCollisionShape* GetShape() {
				return shape;
			}
			inline btVector3 CalculateLocalInertia(float mass) {
				if ( local_inertia_supported ) {
					btVector3 inertia;
					shape->calculateLocalInertia(mass, inertia);
					return inertia;
				}
				else return btVector3(0, 0, 0);
			}
			
			static void Wrap(scripting::Script *script);
			
		};
		
		
		/** A --STATIC-- convex or concave collision shape built around a SkinnedMesh instance */
		class MeshCollisionShape : public CollisionShape {
			btTriangleMesh *triangle_mesh;
			btTriangleInfoMap *triangle_map;
			
			void LoadMesh(video::SkinnedMesh *mesh, const FVec3 &scaling);
			
			
		public:
			MeshCollisionShape(video::SkinnedMesh *mesh, const FVec3 &scaling);
			virtual ~MeshCollisionShape();
			
			
			static void Wrap(scripting::Script *script);
		};
		
		/** An infinitely long plane collision shape */
		class PlaneCollisionShape : public CollisionShape {
		public:
			inline PlaneCollisionShape(const FVec3 &normal, float constant) : CollisionShape(new btStaticPlaneShape(VectorGLMToBullet(normal), constant)) {
				
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		/** A cylinder collision shape */
		class CylinderCollisionShape : public CollisionShape {
		public:
			inline CylinderCollisionShape(float radius, float height) : CollisionShape(new btCylinderShape(btVector3(radius, height, radius))) {
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		/** A box collision shape */
		class BoxCollisionShape : public CollisionShape {
		public:
			inline BoxCollisionShape(const FVec3 &half_extents) : CollisionShape(new btBoxShape(VectorGLMToBullet(half_extents))) {
				
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		/** A capsule collision shape (cylinder + 2 semispheres) */
		class CapsuleCollisionShape : public CollisionShape {
		public:
			inline CapsuleCollisionShape(float radius, float height) : CollisionShape(new btCapsuleShape(radius, height)) {
				
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		/** A sphere collision shape */
		class SphereCollisionShape : public CollisionShape {
		public:
			inline SphereCollisionShape(float radius) : CollisionShape(new btSphereShape(radius)) {
				
			}
			
			static void Wrap(scripting::Script *script);
		};
		
		
	}
}

#endif /* CollisionShape_hpp */
