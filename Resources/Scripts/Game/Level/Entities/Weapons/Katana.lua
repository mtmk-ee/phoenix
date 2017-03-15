
local Class = Class or require("Scripts.Class")
local Level = Level or require("Scripts.Game.Level.Level")
local Entity = Entity or require("Scripts.Game.Level.Entities.Entity")
local Weapon = Weapon or require("Scripts.Game.Level.Entities.Weapons.Weapon")

Katana = Class:new(Weapon)




function Katana:Fire()
  
end

function Katana:SetPosition(position)
  self.position = position
end

function Katana:SwitchTo()
  self.current_camera_rotation = FVec3(90, 0, 0)
  self.current_camera_translation = FVec3(0.25, -1, -0.3)
  self.translate_camera_to = FVec3(0.13, -0.2, -0.3)
  self:SetAimDownSights(false)
end

function Katana:SwitchAway()
  self.rotate_camera_to = FVec3(0, 0, 0)
end

function Katana:SetAimDownSights(aim_down_sights)
  self.aim_down_sights = aim_down_sights
  
  if ( aim_down_sights ) then
    self.rotate_camera_to = FVec3(90, 0, 0)
    self.translate_camera_to = FVec3(0, -0.25, -0.2)
  else
    self.rotate_camera_to = FVec3(90, 0, 0)
    self.translate_camera_to = FVec3(0.13, -0.2, -0.3)
  end
end

-- Returns the rotation needed by the first-person camera
function Katana:GetCameraRotation()
  return Matrix.CreateRotationTransform(self.current_camera_rotation)
end
-- Returns the translation needed by the first-person camera
function Katana:GetCameraTranslation()
  return Matrix.CreateTranslationTransform(self.current_camera_translation)
end



function Katana:TransformToBone(mesh, bone, bone2)
  local bone_transform = Matrix.MultiplyFMat4(mesh:GetCorrectionMatrix(), Matrix.MultiplyFMat4(bone.global_transform, bone.local_transform))
  
  local translation_offset = Matrix.CreateTranslationTransform(FVec3(0.15, 0.035, -0.02))
  local rotation = Matrix.MultiplyFMat4(Matrix.CreateRotationTransform(FVec3(-5,120, -70)), self.recoil_transform)
  
  local bone_angle = mesh:GetBoneAngle(bone, bone2)
  local rotation_2 = Matrix.MultiplyFMat4(rotation, Matrix.CreateRotationTransform(bone_angle))
  local model_matrix = Matrix.MultiplyFMat4(bone_transform, Matrix.MultiplyFMat4(rotation, translation_offset))
  model_matrix = Matrix.MultiplyFMat4(mesh:GetModelMatrix(), model_matrix)
  
  self.mesh:SetModelMatrix(model_matrix)
end

function Katana:Update(update_info)
  local delta_time = update_info.delta_time:Seconds()
  
  local drx = self.rotate_camera_to.x - self.current_camera_rotation.x
  local dry = self.rotate_camera_to.y - self.current_camera_rotation.y
  local drz = self.rotate_camera_to.z - self.current_camera_rotation.z
  local dtx = self.translate_camera_to.x - self.current_camera_translation.x
  local dty = self.translate_camera_to.y - self.current_camera_translation.y
  local dtz = self.translate_camera_to.z - self.current_camera_translation.z
  local translate_dir = 1
  local rotate_dir = 1
  
  if ( math.abs(drx) < 0.0001 and math.abs(dry) < 0.0001 and math.abs(drz) < 0.0001 ) then
    self.current_camera_rotation = self.rotate_camera_to
  else
    local nrx = self.current_camera_rotation.x + drx * delta_time * 8
    local nry = self.current_camera_rotation.y + dry * delta_time * 8
    local nrz = self.current_camera_rotation.z + drz * delta_time * 8
    
    self.current_camera_rotation = FVec3(nrx, nry, nrz)
  end
  
  if ( math.abs(dtx) < 0.0001 and math.abs(dty) < 0.0001 and math.abs(dtz) < 0.0001 ) then
    self.current_camera_translation = self.translate_camera_to
  else
    local ntx = self.current_camera_translation.x + dtx * delta_time * 8
    local nty = self.current_camera_translation.y + dty * delta_time * 8
    local ntz = self.current_camera_translation.z + dtz * delta_time * 8
    
    self.current_camera_translation = FVec3(ntx, nty, ntz)
  end
  
end

function Katana:Render(render_info, level)
  self.mesh:GetShaderProgram():UseProgram()
  self.mesh:GetShaderProgram():SetUniformFloat("ambient_intensity", 0.1)
  self.mesh:GetShaderProgram():SetUniformFloat("diffuse_intensity", 1)
  self.mesh:GetShaderProgram():SetUniformFVec3("light_pos", level.light_position)
  self.mesh:Render(level.entities["Player"].camera)
end


function Katana:__new(level)
  
  self:Init(level)
  
  self.position = FVec3(0, 1.5, 0)
  self.mesh = SkinnedMesh("Colt")
  
  if not self.mesh:LoadMesh(level.game.models_folder .. "/Weapons/Katana/Katana.obj") then
    print "Error loading model 'Katana.obj'"
  else
    
    local scale = 0.5
    self.mesh:SetScaleMatrix(Matrix.CreateScaleTransform(FVec3(scale, scale, scale)))
    self.mesh:SetModelMatrix(Matrix.CreateTranslationTransform(FVec3(3, 0, 0)))
    self.mesh:SetCorrectionMatrix(Matrix.CreateRotationTransform(FVec3(0, 90, 0)))
    
    self.is_gun = true
    self.is_automatic = false
    
    
    self.aim_down_sights = false
    -- Used for the main character's gun
    self.translate_camera_to = FVec3(0.13, -0.2, -0.3)
    self.rotate_camera_to = FVec3(0, 0, 0)
    self.current_camera_translation = FVec3(0.13, -1, 0)
    self.current_camera_rotation = FVec3(90, 0, 0)
    
    self.position = FVec3(0, 0, 0)
    
  end
  
  
end




return Katana

