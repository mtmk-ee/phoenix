
local Class = Class or require("Scripts.Class")
local Level = Level or require("Scripts.Game.Level.Level")
local Entity = Entity or require("Scripts.Game.Level.Entities.Entity")
local Gun = Gun or require("Scripts.Game.Level.Entities.Weapons.Gun")


Colt = Class:new(Gun)


function Colt:Fire()
  self.recoil = self.recoil + 1
  if ( self.recoil > self.recoil_max ) then
    self.recoil = self.recoil_max
  end
  
  AudioManager:PlaySound(Engine:GetPlatform():GetGameFolder() .. "/Sounds/Weapons/Colt/Colt.wav", self.position)
end

function Colt:SetPosition(position)
  self.position = position
end

function Colt:SwitchTo()
  self.current_camera_rotation = FVec3(0, 100, 0)
  self.current_camera_translation = FVec3(0.1, -0.3, 0)
  self:SetAimDownSights(false)
end

function Colt:SwitchAway()
  self.rotate_camera_to = FVec3(0, 0, 0)
end

function Colt:SetAimDownSights(aim_down_sights)
  self.aim_down_sights = aim_down_sights
  
  if ( aim_down_sights ) then
    self.rotate_camera_to = FVec3(2.5, 90, 0)
    self.translate_camera_to = FVec3(0, -0.1, -0.2)
  else
    self.rotate_camera_to = FVec3(0, 100, 0)
    self.translate_camera_to = FVec3(0.1, -0.1, -0.2)
  end
end

-- Returns the rotation needed by the first-person camera
function Colt:GetCameraRotation()
  return Matrix.MultiplyFMat4(Matrix.CreateRotationTransform(self.current_camera_rotation), self.recoil_transform)
end
-- Returns the translation needed by the first-person camera
function Colt:GetCameraTranslation()
  return Matrix.CreateTranslationTransform(self.current_camera_translation)
end



function Colt:TransformToBone(mesh, bone, bone2)
  local bone_transform = Matrix.MultiplyFMat4(mesh:GetCorrectionMatrix(), Matrix.MultiplyFMat4(bone.global_transform, bone.local_transform))
  
  local translation_offset = Matrix.CreateTranslationTransform(FVec3(0.15, 0.035, -0.02))
  local rotation = Matrix.MultiplyFMat4(Matrix.CreateRotationTransform(FVec3(-5,120, -70)), self.recoil_transform)
  
  local bone_angle = mesh:GetBoneAngle(bone, bone2)
  local rotation_2 = Matrix.MultiplyFMat4(rotation, Matrix.CreateRotationTransform(bone_angle))
  local model_matrix = Matrix.MultiplyFMat4(bone_transform, Matrix.MultiplyFMat4(rotation, translation_offset))
  model_matrix = Matrix.MultiplyFMat4(mesh:GetModelMatrix(), model_matrix)
  
  self.mesh:SetModelMatrix(model_matrix)
end

function Colt:Update(update_info)
  local delta_time = update_info.delta_time:Seconds()
  
  if ( self.recoil > 0 ) then
    local recoil_rotation = math.sin(self.recoil * self.recoil_speed * math.pi / 180) * self.recoil_max_angle
    self.recoil = self.recoil - delta_time * 4
    self.recoil_transform = Matrix.CreateRotationTransform(FVec3(0, 0, recoil_rotation))
  else
    self.recoil = 0
    self.recoil_transform = FMat4(1.0)
  end
  
  
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

function Colt:Render(render_info, level)
  self.mesh:GetShaderProgram():UseProgram()
  self.mesh:GetShaderProgram():SetUniformFloat("ambient_intensity", 0.1)
  self.mesh:GetShaderProgram():SetUniformFloat("diffuse_intensity", 1)
  self.mesh:GetShaderProgram():SetUniformFVec3("light_pos", level.light_position)
  self.mesh:Render(level.entities["Player"].camera)
end


function Colt:__new(level)
  
  self:Init(level)
  self.level = level
  
  self.position = FVec3(0, 1.5, 0)
  self.mesh = SkinnedMesh("Colt")
  
  if not self.mesh:LoadMesh(level.game.models_folder .. "/Weapons/Colt/Colt.obj") then
    print "Error loading model 'Colt.obj'"
  else
    
    local scale = 0.145
    self.mesh:SetScaleMatrix(Matrix.CreateScaleTransform(FVec3(scale, scale, scale)))
    self.mesh:SetModelMatrix(Matrix.CreateTranslationTransform(FVec3(3, 00, 0)))
    self.mesh:SetCorrectionMatrix(Matrix.CreateRotationTransform(FVec3(0, 90, 0)))
    
    self.is_gun = true
    self.is_automatic = false
    
    self.recoil_max_angle = -20
    self.recoil_max = 1
    self.recoil_speed = 20
    self.recoil = 0
    self.recoil_transform = FMat4(1.0)
    
    self.aim_down_sights = false
    -- Used for the main character's gun
    self.translate_camera_to = FVec3(0.1, -0.1, -0.2)
    self.rotate_camera_to = FVec3(0, 100, 0)
    self.current_camera_translation = FVec3(0.3, -1.2, 0)
    self.current_camera_rotation = FVec3(0, 0, 0)
    
    self.position = FVec3(0, 0, 0)
    
    -- Audio
    self.sound = Sound(Engine:GetPlatform():GetGameFolder() .. "/Sounds/Weapons/Colt/colt.mp3")
  end
  
  
end




return Colt

