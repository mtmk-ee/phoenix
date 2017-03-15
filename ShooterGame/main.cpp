//
//  main.cpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#include <iostream>
#include "Engine.hpp"
#include "Game/ShooterGame.hpp"


using namespace phoenix;
using namespace shootergame;





int main(int argc, char *argv[]) {
	
	// Find the game folder
	std::string user_folder = Environment::Current()->GetUserFolder();
	std::string game_folder = user_folder + "/Applications/ShooterGame/Resources";
	
	
	// Create a platform for the engine
	Platform *platform = new Platform(argc, argv);
	platform->SetGameFolder("/Users/mmatsumori-kelly17/Desktop/ShooterGame/Resources");
	
	
	// Create the engine
	Engine *engine = Engine::New(platform);
	ShooterGame *game = new ShooterGame();
	ShooterGame::Wrap(engine->GetSceneManager()->GetMainScript());
	engine->SetGame(game);
	engine->Start();
	
	
	// Delete the engine
	Engine::Delete(engine);
	
	delete platform;
	delete game;
	
    return 0;
}
