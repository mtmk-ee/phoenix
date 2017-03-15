//
//  Sound.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 3/4/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include "Sound.hpp"
#include "../../Util/Debug.hpp"
#include "../../Scripting/Script.hpp"
using namespace phoenix::scene::audio;


Sound::Sound(const std::string &file) {
	
	
	
}
Sound::~Sound() {
	
}


void Sound::LoadFile(const std::string &file) {
	
}

void Sound::Wrap(scripting::Script *script) {
	script->GetGlobalNamespace()
	.beginClass<Sound>("Sound")
	.addConstructor<void (*) (const std::string&)>()
	.addFunction("SetSoundSource", &Sound::SetSoundSource)
	.addFunction("Play", &Sound::Play)
	.endClass();
}



