//
//  VertexInfo.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/20/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef VertexInfo_hpp
#define VertexInfo_hpp

#include "../Util/Vector.hpp"

namespace phoenix {
	namespace video {
		
		
		/** Information about a vertex */
		struct Vertex {
			FVec3 vertex;
			FVec2 uv;
			FVec3 normal;
			
			inline Vertex() : vertex(), normal(), uv() {
				
			}
			inline Vertex(const FVec3 &vertex, const FVec3 &normal, const FVec2 &uv) : vertex(vertex), normal(normal), uv(uv) {
				
			}
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
	}
}

#endif /* VertexInfo_hpp */
