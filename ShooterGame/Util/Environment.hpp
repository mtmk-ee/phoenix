//
//  Environment.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/12/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Environment_hpp
#define Environment_hpp

#include "File.hpp"


namespace phoenix {
	
	
	
	
	
	
	/** Information about the execution environment */
	class Environment {
		static Environment singleton;
		std::string user_name;
		std::string user_folder;
		
		
		/** Hidden constructor */
		Environment();
		/** Hidden destructor */
		~Environment();
	public:
		/** Returns the current enivronment */
		static Environment *Current() {
			return &singleton;
		}
		
		
		
		/** Returns the user's username */
		const inline std::string &GetUserName() const {
			return user_name;
		}
		/** Returns the user's folder */
		inline const std::string &GetUserFolder() const {
			return user_folder;
		}
		
		
	};
	
	
	
	
#define __IS_UNIX false
#define __IS_LINUX false
#define __IS_APPLE false
#define __IS_WINDOWS false
#define __IS_64_BIT false
	
	
	
	
	// Unix
#if defined(unix) || defined(__unix) || defined(__unix__)
#undef __IS_UNIX
#define __IS_UNIX true
#endif
	
	
	// Linux
#if defined(__linux__)
#undef __IS_LINUX
#undef __IS_UNIX
#define __IS_LINUX true
#define __IS_UNIX  true
#endif
	
	
	// Mac
#if defined(__APPLE__) || defined(__MACH__)
#undef  __IS_APPLE
#undef  __IS_UNIX
#define __IS_APPLE true
#define __IS_UNIX  true
#endif
	
	
	// Windows
#if defined(_WIN32)
#undef  __IS_WINDOWS
#define __IS_WINDOWS true
	
#if defined(_WIN64)
#undef  __IS_64_BIT
#define __IS_64_BIT true
#endif
#endif
	
	
	// 32 bit vs 64 bit
#if __GNUC__
#if __x86_64__ || __ppc64__
#undef __IS_64_BIT
#define __IS_64_BIT true
#endif
#endif
	
	
	
	
	// Debug mode
#ifndef PHOENIX_UTIL_DEBUG_MODE
#define PHOENIX_UTIL_DEBUG_MODE true
#endif
	
	
	

	
	
	
	
}

#endif /* Environment_hpp */
