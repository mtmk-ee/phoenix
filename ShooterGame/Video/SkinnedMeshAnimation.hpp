//
//  SkinnedMeshAnimation.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/28/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef SkinnedMeshAnimation_hpp
#define SkinnedMeshAnimation_hpp

#include "../Update.hpp"


namespace phoenix {
	namespace video {
		
		
		
		class SkinnedMeshAnimation {
			
		public:
			SkinnedMeshAnimation();
			~SkinnedMeshAnimation();
			
			
			
			void Update(const UpdateInfo &update_info);
			
			
		};
		
		
		
	}
}

#endif /* SkinnedMeshAnimation_hpp */
