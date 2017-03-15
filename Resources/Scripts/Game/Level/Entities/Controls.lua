
local Class = Class or require("Scripts.Class")

Controls = Class:new()



function Controls:IsControlActive(name)
  if ( self.control_types[name] == 0 ) then
    return Keyboard:IsKeyPressed(self.controls[name])
  else
    return Mouse:IsButtonPressed(self.controls[name])
  end
end

-- Adds or replaces a control. Control type can either be 0 for keyboard or 1 for mouse
function Controls:AddControl(name, value, control_type)
  self.controls[name] = value
  self.control_types[name] = control_type
end


function Controls:LoadDefaults()
  self:AddControl("forward", "w", 0)
  self:AddControl("backward", "s", 0)
  self:AddControl("left", "a", 0)
  self:AddControl("right", "d", 0)
  self:AddControl("jump", "space", 0)
  self:AddControl("run", "q", 0)
  
  self:AddControl("aim", "tab", 0)
  self:AddControl("fire", 0, 1)
  
  self:AddControl("weapon1", "1", 0)
  self:AddControl("weapon2", "2", 0)
  self:AddControl("weapon3", "3", 0)
  self:AddControl("cycle", "e", 0)
end


function Controls:__new()
  
  self.controls = {}
  self.control_types = {}
  self:LoadDefaults()
  
end



return Controls
