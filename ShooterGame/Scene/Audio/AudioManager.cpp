//
//  AudioManager.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/4/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "AudioManager.hpp"
#include "../../Util/Debug.hpp"
#include "../../Scripting/Script.hpp"


using namespace phoenix::scene::audio;





AudioManager::AudioManager() {
	
	sound_engine = irrklang::createIrrKlangDevice();
	
	
	// Set listener info
	SetListenerPosition(FVec3(0, 0, 0), FVec3(0, 0, 1));
	
	
}
AudioManager::~AudioManager() {
	sound_engine->drop();
}




void AudioManager::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<AudioManager>("AudioManager")
	.addFunction("SetListenerPosition", &AudioManager::SetListenerPosition)
	.addFunction("PlaySound", &AudioManager::PlaySound)
	.endClass();
	
	Sound::Wrap(script);
}





