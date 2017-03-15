//
//  OpenGL.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/23/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "OpenGL.hpp"
#include "../Util/Debug.hpp"

using namespace phoenix;


void video::PrintOpenGLErrors() {
	GLuint error = glGetError();
	
	
	
	// No error, so notify that there were none
	if ( error == GL_NO_ERROR ) {
		LogError("OpenGL Error: no error");
	}
	// Loop through all the errors
	else {
		do {
			// Convert the error code to a string
			std::string error_string;
			switch ( error ) {
				case GL_INVALID_ENUM:
					error_string = "Invalid Enum";
					break;
				case GL_INVALID_VALUE:
					error_string = "Invalid Value";
					break;
				case GL_OUT_OF_MEMORY:
					error_string = "Out of Memory";
					break;
				default:
					error_string = "Unknown error code";
					break;
			}
			
			// Log the error
			LogError("OpenGL Error: %s", error_string.c_str());
		} while ( (error = glGetError()) != GL_NO_ERROR );
	}
}




