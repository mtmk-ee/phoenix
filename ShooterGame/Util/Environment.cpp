//
//  Environment.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/12/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Environment.hpp"
#include <unistd.h>
#include <iostream>
using namespace phoenix;

#if __IS_UNIX
#include <pwd.h>
#endif





Environment Environment::singleton = Environment();
Environment::Environment() {
	
	
	/* Unix Platform */
	#if __IS_UNIX
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	
	
	if ( pw ) {
		user_name = pw->pw_name;
		user_folder = std::string("/Users/") + user_name;
	}
	
	#endif
	
}
Environment::~Environment() {
	
}