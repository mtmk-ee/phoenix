//
//  DebugDrawer.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/6/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef DebugDrawer_hpp
#define DebugDrawer_hpp

#include "btIDebugDraw.h"
#include <OpenGL/gl3.h>
#include "../Video/Shader.hpp"

namespace phoenix {
	namespace scene {
		
		
		class DebugDrawer : public btIDebugDraw {
		public:
			DebugDrawer();
			
			void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix)
			{
				program->UseProgram();
				program->SetUniformFMat4("projection", pProjectionMatrix);
				program->SetUniformFMat4("view", pViewMatrix);
			}
			
			virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
			{
				// Vertex data
				GLfloat points[12];
				
				points[0] = from.x();
				points[1] = from.y();
				points[2] = from.z();
				points[3] = color.x();
				points[4] = color.y();
				points[5] = color.z();
				
				points[6] = to.x();
				points[7] = to.y();
				points[8] = to.z();
				points[9] = color.x();
				points[10] = color.y();
				points[11] = color.z();
				
				glDeleteBuffers(1, &VBO);
				glDeleteVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);
				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
				glBindVertexArray(0);
				
				glBindVertexArray(VAO);
				glDrawArrays(GL_LINES, 0, 2);
				glBindVertexArray(0);
			}
			virtual void drawContactPoint(const btVector3 &, const btVector3 &, btScalar, int, const btVector3 &) {}
			virtual void reportErrorWarning(const char *) {}
			virtual void draw3dText(const btVector3 &, const char *) {}
			virtual void setDebugMode(int p) {
				m = p;
			}
			int getDebugMode(void) const { return 3; }
			int m;
			GLuint VAO = 0;
			GLuint VBO = 0;
			
			
			video::ShaderProgram *program;
		};
		
		
	}
}

#endif /* DebugDrawer_hpp */
