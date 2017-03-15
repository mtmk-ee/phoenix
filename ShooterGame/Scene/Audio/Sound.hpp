//
//  Sound.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/4/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Sound_hpp
#define Sound_hpp

#include "../../Util/Vector.hpp"
#include <OpenALSoft/AL/al.h>
#include <OpenALSoft/AL/alc.h>
#include <OpenALSoft/AL/alext.h>
#include <vector>
#include <string>


namespace phoenix {
	namespace scripting { class Script; }
	
	namespace scene {
		namespace audio {
			class AudioManager;
			
#define NUM_STREAM_BUFFERS 4
			
			struct StreamPlayer {
				ALuint buffers[NUM_STREAM_BUFFERS];
				ALuint source;
				
				ALenum format;
				ALenum channels;
				ALenum type;
				ALuint rate;
			};
			
			
			
			class Sound {
				
				
				void LoadFile(const std::string &file);
				
			public:
				Sound(const std::string &file);
				~Sound();
				
				
				
				inline void SetSoundSource(const FVec3 &source) {
					
				}
				
				
				inline void Play() {
					
				}
				
				
				static void Wrap(scripting::Script *script);
			};
			
			
			
		}
	}
}

#endif /* Sound_hpp */
