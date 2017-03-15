
local Class = Class or require("Scripts.Class")

HumanRig = Class:new()

local light_angle = 0

function HumanRig:Update(update_info)
  local delta_time = update_info.delta_time:Seconds()
  local ticks_per_second = 60
  self.tick = self.tick + delta_time * 2
  
  local to_radians = math.pi / 180
  local to_degrees = 180 / math.pi
  
  
  
  
  -- Arms
  local angle = math.sin(self.tick) * 50
  
  local upperarm_l_transform = Matrix.CreateRotationTransform(FVec3(angle, 0, 30))
  self.mesh:SetBoneTransform("upperarm_l", upperarm_l_transform)
  
  local upperarm_r_transform = Matrix.CreateRotationTransform(FVec3(-angle, 0, -30))
  self.mesh:SetBoneTransform("upperarm_r", upperarm_r_transform)
   
  
  angle = math.sin(self.tick) * 50
  if angle > 0 then angle = 0 end
  local lowerarm_l_transform = Matrix.CreateRotationTransform(FVec3(angle, 0, 0))
  self.mesh:SetBoneTransform("lowerarm_l", lowerarm_l_transform)
  
  angle = -math.sin(self.tick) * 50
  if angle > 0 then angle = 0 end
  
  local lowerarm_r_transform = Matrix.CreateRotationTransform(FVec3(angle, 0, 0))
  self.mesh:SetBoneTransform("lowerarm_r", lowerarm_r_transform)
  
  -- Legs
  angle = math.sin(self.tick) * 30
  local transform = Matrix.MultiplyFMat4(Matrix.CreateRotationTransform(FVec3(angle, 0, -8)), Matrix.CreateRotationTransform(FVec3(0, -8, 0)))
  self.mesh:SetBoneTransform("thigh_l", transform)
  
  angle = -math.sin(self.tick) * 30
  local transform = Matrix.MultiplyFMat4(Matrix.CreateRotationTransform(FVec3(angle, 0, 8)), Matrix.CreateRotationTransform(FVec3(0, 8, 0)))
  self.mesh:SetBoneTransform("thigh_r", transform)
  
  
  angle = math.sin(self.tick) * 50
  if angle > 0 then angle = 0 end
  local transform = Matrix.CreateRotationTransform(FVec3(angle, 0, 0))
  self.mesh:SetBoneTransform("calf_l", transform)
  
  angle = -math.sin(self.tick) * 50
  if angle > 0 then angle = 0 end
  
  local transform = Matrix.CreateRotationTransform(FVec3(angle, 0, 0))
  self.mesh:SetBoneTransform("calf_r", transform)
  
  -- Head
  angle = -math.sin(self.tick) * 10
  
  local transform = Matrix.CreateRotationTransform(FVec3(0, 0, angle))
  self.mesh:SetBoneTransform("head", transform)
  
  angle = math.sin(self.tick) * 10
  
  local transform = Matrix.CreateRotationTransform(FVec3(0, 0, angle))
  self.mesh:SetBoneTransform("neck_01", transform)
  
  
  
  
  self.mesh:UpdateSkeleton()
end

function HumanRig:Render(render_info, level)
  
  
  self.mesh:GetShaderProgram():UseProgram()
  self.mesh:GetShaderProgram():SetUniformFloat("ambient_intensity", 0.1)
  self.mesh:GetShaderProgram():SetUniformFloat("diffuse_intensity", 0.5)
  self.mesh:GetShaderProgram():SetUniformFVec3("light_pos", level.light_position)
  self.mesh:Render(level.entities["Player"].camera)
end


function HumanRig:__new(rig_name, rig_file)
  
  self.tick = 0
  
  
  
  
  -- Load mesh
  self.mesh = SkinnedMesh(rig_name)
  if not self.mesh:LoadMesh(rig_file) then
    LogError("Could not load rig '" .. rig_name .. "'")
  else
    self.mesh:SetCorrectionMatrix(Matrix.CreateRotationTransform(FVec3(90, 90, 180)))
  end
  
  
end




return HumanRig


