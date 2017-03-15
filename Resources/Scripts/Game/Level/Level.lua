
local Class = Class or require("Scripts.Class")


Level = Class:new()



function Level:Update(update_info)
  
end
function Level:Render(render_info)
  
end


function Level:Init(game, name)
  self.game = game
  self.name = name
  self.light_position = FVec3(0, 0, 0)
end


function Level:__new(game, name)
  self:Init(name)
end





return Level
