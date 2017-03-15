//
//  ShooterGame.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/17/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef ShooterGame_hpp
#define ShooterGame_hpp

#include "../Game.hpp"


namespace shootergame {
	
	class ShooterGame : public phoenix::Game {
		
		
	public:
		ShooterGame();
		virtual ~ShooterGame();
		
		
		
		virtual void Start() override;
		virtual void Stop() override;
		virtual void Update(const phoenix::UpdateInfo &info) override;
		virtual void Render(const phoenix::RenderInfo &info) override;
		
		
		
		static void Wrap(phoenix::scripting::Script *script);
	};
	
	
}

#endif /* ShooterGame_hpp */
