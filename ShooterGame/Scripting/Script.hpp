//
//  Script.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/9/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Script_hpp
#define Script_hpp

extern "C" {
# include <lua/lua.h>
# include <lua/lauxlib.h>
# include <lua/lualib.h>
}
#include <LuaBridge/LuaBridge.h>



namespace phoenix {
	namespace scripting {
		
		
		/** A script. Only one should be needed per game, but more are possible. */
		class Script {
			lua_State *state;
			std::mutex script_mutex;
			
			
			void Init();
			
		public:
			Script();
			Script(const std::string &file);
			~Script();
			
			/** Returns the mutex for this resource */
			inline std::mutex& GetMutex() {
				return script_mutex;
			}
			
			
			
			/** Returns a global member */
			inline luabridge::LuaRef Get(const std::string &name) {
				return luabridge::getGlobal(state, name.c_str());
			}
			
			
			/** Returns the lua global namespace */
			inline luabridge::Namespace GetGlobalNamespace() {
				return luabridge::getGlobalNamespace(state);
			}
			
			/** Sets a global variable to the given value */
			template <typename T>
			inline void Set(const std::string &name, const T &value) {
				luabridge::setGlobal(state, value, name.c_str());
			}
			
			
			/** Evaluates a file */
			bool EvalFile(const std::string &file);
			/** Evaluates some code with no result */
			bool EvalString(const std::string &script);
		};
		
		
		/** Wraps a Lua-side member function */
		struct MemberFunctionCallback {
			luabridge::LuaRef self, function;
			
			inline MemberFunctionCallback(luabridge::LuaRef self, luabridge::LuaRef function) : self(self), function(function) {
				
			}
			
			/** Calls the Lua member function. Lock the script mutex before using this function */
			template <typename... Args>
			inline void Call(Args... args) {
				if ( self.isTable() && function.isFunction() ) {
					function(self, args...);
				}
			}
			
			
			static void Wrap(Script *script);
		};
	}
	
	
	
	
	
	
	
	class LuaRefArray2D {
		
		
		
		
		
		
		
		
	};
	
	
	
	
	
	
}

#endif /* Script_hpp */
