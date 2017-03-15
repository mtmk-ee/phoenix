//
//  AudioManager.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/4/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef AudioManager_hpp
#define AudioManager_hpp

#include "Sound.hpp"
#include <irrKlang/irrKlang.h>


namespace phoenix {
	namespace scene {
		namespace audio {
			
			
			
			class AudioManager {
				irrklang::ISoundEngine *sound_engine;
				
			public:
				AudioManager();
				~AudioManager();
				
				
				/** Sets the position of the listener */
				inline void SetListenerPosition(const FVec3 &position, const FVec3 &look_dir) {
					sound_engine->setListenerPosition(irrklang::vec3df(position.x, position.y, position.z), irrklang::vec3df(look_dir.x, look_dir.y, look_dir.z));
				}
				/** Plays a sound */
				inline void PlaySound(const std::string &file, const FVec3 &position) {
					sound_engine->play3D(file.c_str(), irrklang::vec3df(position.x, position.y, position.z));
				}
				
				
				static void Wrap(scripting::Script *script);
				
			};
			
			
			
			
		}
	}
}

#endif /* AudioManager_hpp */
