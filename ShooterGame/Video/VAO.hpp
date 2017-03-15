//
//  VAO.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/14/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef VAO_hpp
#define VAO_hpp


#include "Vertex.hpp"
#include <vector>

namespace phoenix {
	namespace video {
		
		
		
		
		
		
		
		/** A model with manually added vertex data */
		class VAO {
			unsigned int vao, vbo;
			bool created;
			
			std::vector<Vertex> vertex_data;
			
			inline VAO() : created(false) { }
		public:
			static inline VAO* New() {
				return new VAO();
			}
			static inline void Delete(VAO *vao) {
				delete vao;
			}
			~VAO();
			
			
			/** Reserves some data in memory */
			inline void ReserveData(long count) {
				vertex_data.reserve(count);
			}
			/** Adds vertex info to this vao */
			inline void AddVertex(const Vertex &vertex) {
				vertex_data.push_back(vertex);
			}
			
			/** Create the VAO */
			bool Create();
			/** Destroy the VAO for reuse */
			void Destroy();
			/** Checks if the VAO was created */
			inline bool IsCreated() const {
				return created;
			}
			
			
			/** Return vertex info */
			inline std::vector<Vertex>& GetVertices() {
				return vertex_data;
			}
			
			
			/** Render the model */
			void Render();
			
			
			
			
			static void Wrap(scripting::Script *script);
		};
		
		
		
		
	}
}

#endif /* VAO_hpp */
