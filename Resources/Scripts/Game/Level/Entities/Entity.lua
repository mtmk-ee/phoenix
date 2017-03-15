
local Class = Class or require("Scripts.Class")


Entity = Class:new()






function Entity:Init(level)
  self.level = level
  
  self.position = FVec3(0, 0, 0)
  self.rotation = FVec3(0, 0, 0)
  self.scene_object = level.scene:CreateSceneObject()
  
  
end


function Entity:__new(level)
  self:Init(level)
end



return Entity
