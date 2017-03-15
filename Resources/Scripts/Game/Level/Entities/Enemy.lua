
local Class = Class or require("Scripts.Class")
local Entity = Entity or require("Scripts.Game.Level.Entities.Entity")
local HumanRig = HumanRig or require("Scripts.Game.Level.Entities.HumanRig")
local Colt = Colt or require("Scripts.Game.Level.Entities.Weapons.Colt")


Enemy = Class:new(Entity)


function Enemy:SetPosition(position)
  self.position = position
  self.rigid_body:SetPosition(position)
end


function Enemy:Update(update_info)
  
  self.position = self.rigid_body:GetPosition()
  
  local player = self.level.entities["Player"]
  local angle_to_player = math.atan2(player.position.z - self.position.z, player.position.x - self.position.x) * 180 / math.pi
  
  -- Apply a movement force
  local move_force = FVec3(0, 0, 0)
  move_force.x = math.cos(angle_to_player) * self.speed
  move_force.z = math.sin(angle_to_player) * self.speed
  self.rigid_body:ApplyForce(move_force)
  
  
  -- Set enemy rotation
  self.rotation = FVec3(0, 90 - angle_to_player, 0)
  
  
  
  
  
  self.rig:Update(update_info)
  
  -- Update the weapon
  local hand_matrix = self.rig.mesh:GetBoneGlobalTransform("hand_r")
  self.weapon.mesh:SetModelMatrix(Matrix.MultiplyFMat4(self.rig.mesh:GetModelMatrix(), hand_matrix))
  
  
end

function Enemy:Render(render_info)
  local mesh_position = FVec3(self.position.x, self.position.y - self.height / 2, self.position.z)
  self.rig.mesh:SetModelMatrix(Matrix.MultiplyFMat4(Matrix.CreateTranslationTransform(mesh_position), Matrix.CreateRotationTransform(self.rotation)))
  self.rig:Render(render_info, self.level)
  self.weapon:TransformToBone(self.rig.mesh, self.rig.mesh:GetBone("hand_r"), self.rig.mesh:GetBone("lowerarm_r"))
  self.weapon:Render(render_info, self.level)
end


function Enemy:__new(level)
  self:Init(level)
  
  self.rig = HumanRig:new("Lucas", level.game.models_folder .. "/Lucas/Lucas.dae") 
  
  self.scene_object:AddUpdateFunction(MemberFunctionCallback(self, self.Update))
  self.scene_object:AddRenderFunction(MemberFunctionCallback(self, self.Render))
  
  self.speed = (math.random() + 1) * 0.5
  self.weapon = Colt:new(level)
  
  
  self.mass = 70
  self.radius = 0.2
  self.height = 1.8
  
  self.collision_shape = CapsuleCollisionShape(self.radius, self.height)
  self.rigid_body = RigidBody(self.collision_shape, self.mass)
  self.rigid_body:SetDamping(0.9, 1)
  self.level.scene:GetPhysicsWorld():AddRigidBody(self.rigid_body)
  
  -- Set rigid body position
  self.position = FVec3(0, self.height / 2 + 0.1, 0)
  self.rigid_body:SetPosition(self.position)
  
  
  -- Rig
  local finger_transforms = {}
  finger_transforms[1] = Matrix.CreateRotationTransform(FVec3(-30, 0, 0))
  finger_transforms[2] = Matrix.CreateRotationTransform(FVec3(-30, 0, 0))
  finger_transforms[3] = Matrix.CreateRotationTransform(FVec3(-70, 0, 0))
  
  for i = 1, 3 do
    self.rig.mesh:SetBoneTransform("index_0" .. i .. "_r", finger_transforms[i])
    self.rig.mesh:SetBoneTransform("middle_0" .. i .. "_r", finger_transforms[i])
    self.rig.mesh:SetBoneTransform("ring_0" .. i .. "_r", finger_transforms[i])
    self.rig.mesh:SetBoneTransform("pinky_0" .. i .. "_r", finger_transforms[i])
  end
  
  local new_finger_transform = Matrix.CreateRotationTransform(FVec3(0, 0, 0))
  self.rig.mesh:SetBoneTransform("index_02_r", new_finger_transform)
  
  
  local thumb_transform01 = Matrix.CreateRotationTransform(FVec3(-15, 0, 70))
  self.rig.mesh:SetBoneTransform("thumb_01_r", thumb_transform01)
  local thumb_transform02 = Matrix.CreateRotationTransform(FVec3(15, -30, -50))
  self.rig.mesh:SetBoneTransform("thumb_02_r", thumb_transform02)
  
  
  
end



return Enemy


