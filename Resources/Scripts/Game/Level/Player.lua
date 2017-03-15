
local Class = Class or require("Scripts.Class")

Player = Class:new()



function Player:Update(update_info)
  
  local mouse = Display:GetMouse()
  local keyboard = Display:GetKeyboard()
  
  -- Rotation
  
  local rotation = FVec3(0, 0, 0)
  rotation.x = mouse:GetDeltaY() * update_info.delta_time:Seconds() * 5
  rotation.y = mouse:GetDeltaX() * update_info.delta_time:Seconds() * 5
  self.camera:Rotate(rotation)
  
  
  
  local xm = 0
  local zm = 0
  if keyboard:IsKeyPressed("w") then zm = zm + 1 end
  if keyboard:IsKeyPressed("s") then zm = zm - 1 end
  if keyboard:IsKeyPressed("d") then xm = xm + 1 end
  if keyboard:IsKeyPressed("a") then xm = xm - 1 end
  
  
  local velocity = FVec3(0, 0, 0)
  local forward = self.camera:GetForwardVector()
  local right = self.camera:GetRightVector()
  
  local movement_speed = 3 * update_info.delta_time:Seconds()
  velocity.x = movement_speed * (forward.x * zm + right.x * xm)
  velocity.y = movement_speed * (forward.y * zm + right.y * xm)
  velocity.z = movement_speed * (forward.z * zm + right.z * xm)
  
  self.position.x = self.position.x + velocity.x
  self.position.y = self.position.y + velocity.y
  self.position.z = self.position.z + velocity.z
  
end

function Player:Render(render_info)
  self.camera:SetPosition(self.position)
  self.camera:Update()
end



function Player:__new()
  self.position = FVec3(0, 0, 0)
  self.camera = Camera(1.66, 45, 0.1, 1000)
  
end





return Player



