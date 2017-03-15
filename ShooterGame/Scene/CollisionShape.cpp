//
//  CollisionShape.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/5/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "CollisionShape.hpp"
#include "../Scripting/Script.hpp"
#include "btInternalEdgeUtility.h"
#include "btShapeHull.h"
#include <HACD/hacdHACD.h>

using namespace phoenix;
using namespace phoenix::scene;
using namespace phoenix::video;



CollisionShape::CollisionShape(bool local_inertia_supported) : shape(nullptr), local_inertia_supported(local_inertia_supported) {
	
}
CollisionShape::CollisionShape(btCollisionShape *shape, bool local_inertia_supported) : shape(shape), local_inertia_supported(local_inertia_supported) {
	
}
CollisionShape::~CollisionShape() {
	delete shape;
}



void CollisionShape::Wrap(scripting::Script *script) {
	
	
	script->GetGlobalNamespace()
	.beginClass<CollisionShape>("CollisionShape")
	.endClass();
	
	MeshCollisionShape::Wrap(script);
	PlaneCollisionShape::Wrap(script);
	CylinderCollisionShape::Wrap(script);
	BoxCollisionShape::Wrap(script);
	CapsuleCollisionShape::Wrap(script);
	SphereCollisionShape::Wrap(script);
}





MeshCollisionShape::MeshCollisionShape(video::SkinnedMesh *mesh, const FVec3 &scaling) : CollisionShape(false) {
	LoadMesh(mesh, scaling);
}
MeshCollisionShape::~MeshCollisionShape() {
	delete triangle_mesh;
	delete triangle_map;
}


void MeshCollisionShape::LoadMesh(video::SkinnedMesh *mesh, const FVec3 &scaling) {
	SkinnedMeshBase *base = mesh->GetBase();
	triangle_mesh = new btTriangleMesh();
	
	// Create a compound shape
	btCompoundShape *compound_shape = new btCompoundShape();
	btTransform transform;
	transform.setIdentity();
	
	// Add each mesh to the compound shape
	for (int i = 0; i < base->entries.size(); ++i) {
		MeshEntry &mesh = base->entries[i];
		
		if ( mesh.num_indices > 0 ) {
			// Create a btBvhTriangleMeshShape for the mesh
			btTriangleIndexVertexArray *array = new btTriangleIndexVertexArray(mesh.num_indices / 3, &base->indices[mesh.base_index], sizeof(int) * 3, mesh.num_indices * 3, (btScalar*)&base->vertices[mesh.base_vertex], sizeof(SkinnedVertex));
			btBvhTriangleMeshShape *mesh_shape = new btBvhTriangleMeshShape(array, false);
			
			// Add the mesh to the compound shape
			compound_shape->addChildShape(transform, mesh_shape);
		}
	}
	
	// Set the shape to the compound shape we created
	shape = compound_shape;
}



void MeshCollisionShape::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<MeshCollisionShape, CollisionShape>("MeshCollisionShape")
	.addConstructor<void (*) (SkinnedMesh*, const FVec3&)>()
	.endClass();
}

void PlaneCollisionShape::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<PlaneCollisionShape, CollisionShape>("PlaneCollisionShape")
	.addConstructor<void (*)(const FVec3&, float)>()
	.endClass();
}


void CylinderCollisionShape::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<CylinderCollisionShape, CollisionShape>("CylinderCollisionShape")
	.addConstructor<void (*) (float, float)>()
	.endClass();
}

void BoxCollisionShape::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<BoxCollisionShape, CollisionShape>("BoxCollisionShape")
	.addConstructor<void (*) (const FVec3&)>()
	.endClass();
}

void CapsuleCollisionShape::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<CapsuleCollisionShape, CollisionShape>("CapsuleCollisionShape")
	.addConstructor<void (*) (float, float)>()
	.endClass();
}

void SphereCollisionShape::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.deriveClass<SphereCollisionShape, CollisionShape>("SphereCollisionShape")
	.addConstructor<void (*) (float)>()
	.endClass();
}



