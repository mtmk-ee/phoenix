
local Class = Class or require("Scripts.Class")
local Entity = Entity or require("Scripts.Game.Level.Entities.Entity")
local HumanRig = HumanRig or require("Scripts.Game.Level.Entities.HumanRig")
local HUD = HUD or require("Scripts.Game.Level.Entities.HUD")
local Colt = Colt or require("Scripts.Game.Level.Entities.Weapons.Colt")
local AK47 = AK47 or require("Scripts.Game.Level.Entities.Weapons.AK47")
local Katana = Katana or require("Scripts.Game.Level.Entities.Weapons.Katana")
local Controls = Controls or require("Scripts.Game.Level.Entities.Controls")


Player = Class:new(Entity)

function Player:GetCameraPosition()
  return Vector.AddFVec3(self.position, FVec3(0, self.bob_y, 0))
end

function Player:GetPosition()
  return self.rigid_body:GetPosition()
end

function Player:SetPosition(position)
  self.rigid_body:SetPosition(position)
end

function Player:SetVelocity(velocity)
  self.rigid_body:SetLinearVelocity(velocity)
end

function Player:SwitchToWeapon(weapon)
  if ( self.current_weapon ~= weapon ) then
    self.weapons[self.current_weapon]:SwitchAway()
    self.weapons[weapon]:SwitchTo()
    self.current_weapon = weapon
  end
  self.aim_down_sights = false
end

function Player:SetWeapon(weapon_index, weapon)
  self.weapons[weapon_index] = weapon
end


function Player:Update(update_info)
  local mouse = Display:GetMouse()
  local keyboard = Display:GetKeyboard()
  local delta_time = update_info.delta_time:Seconds()
  
  local center_of_mass = self.rigid_body:GetPosition()
  AudioManager:SetListenerPosition(center_of_mass, self.camera:GetBackwardVector())
  
  -- Rotation
  local rotation = FVec3(0, 0, 0)
  rotation.x = mouse:GetDeltaY() * update_info.delta_time:Seconds() * 5
  rotation.y = mouse:GetDeltaX() * update_info.delta_time:Seconds() * 5
  self.camera:Rotate(rotation)
  
  local xm = 0
  local zm = 0
  local forward_pressed = self.controls:IsControlActive("forward")
  local backward_pressed = self.controls:IsControlActive("backward")
  local left_pressed = self.controls:IsControlActive("left")
  local right_pressed = self.controls:IsControlActive("right")
  local run_pressed = self.controls:IsControlActive("run")
  
  if forward_pressed then zm = zm + 1 end
  if backward_pressed then zm = zm - 1 end
  if right_pressed then xm = xm + 1 end
  if left_pressed then xm = xm - 1 end
  if run_pressed then self.running = true end
  if ( not forward_pressed and not backward_pressed and not left_pressed and not right_pressed ) then
    self.running = false
    self.bob_tick = 0
  end
  
  -- Movement
  local linear_vel = self.rigid_body:GetLinearVelocity()
  local forward = self.camera:GetForwardVector()
  local right = self.camera:GetRightVector()
  
  -- Check if player is on the ground
  local raycast_from = Vector.CopyFVec3(center_of_mass)
  raycast_from.y = raycast_from.y - self.height / 2 + 0.2
  local raycast_to = Vector.CopyFVec3(raycast_from)
  raycast_to.y = raycast_to.y - 0.2
  
  self.is_on_ground = self.level.scene:GetPhysicsWorld():SimpleRaycast(raycast_from, raycast_to)
  if ( not self.is_on_ground ) then
    self.bob_tick = 0
  end
  
  -- Running
  local speed = self.speed
  if ( self.running ) then
    speed = speed * 2
    self.bob_speed = self.base_bob_speed * 2
    self.aim_down_sights = false
  else
    self.bob_speed = self.base_bob_speed
  end
  
  
  local linear_vel = self.rigid_body:GetLinearVelocity()
  local velocity_xz = Vector.CopyFVec3(linear_vel)
  velocity_xz = Vector.AddFVec3(Vector.MultFVec3(forward, zm), Vector.MultFVec3(right, xm))
  velocity_xz.y = 0
  velocity_xz = Vector.MultFVec3(Vector.NormalizeFVec3(velocity_xz), speed)
  velocity_xz.y = self.rigid_body:GetLinearVelocity().y
  
  -- Check if there is the player is moving fast enough to run
  local linear_vel_xz = Vector.CopyFVec3(linear_vel)
  linear_vel_xz.y = 0
  if ( Vector.LengthFVec3(linear_vel) < 0.1 ) then 
    self.running = false
    self.bob_tick = 0
  end
  
  
  
  local jump_force = FVec3(0, 0, 0)
  if ( self.controls:IsControlActive("jump") and linear_vel.y < 0.1 and self.is_on_ground ) then
    jump_force.y = -self.mass * self.level.gravity.y / 2
  end
  
  -- Apply force to rigid body
  self.rigid_body:SetLinearVelocity(velocity_xz)
  self.rigid_body:ApplyForce(jump_force)
  self.position = FVec3(center_of_mass.x, center_of_mass.y + self.height / 2 - 0.15, center_of_mass.z)
  
  -- Switch weapons
  if ( self.controls:IsControlActive("weapon1") ) then
    self:SwitchToWeapon(1)
  elseif ( self.controls:IsControlActive("weapon2") ) then
    self:SwitchToWeapon(2)
  elseif ( self.controls:IsControlActive("weapon3") ) then
    self:SwitchToWeapon(3)
  end
  
  if ( self.controls:IsControlActive("cycle") and not self.was_cycle_key_pressed ) then
    self.was_cycle_key_pressed = true
    
    local new_weapon = self.current_weapon + 1
    if ( new_weapon > self.num_weapons ) then
      new_weapon = 1
    end
    self:SwitchToWeapon(new_weapon)
  elseif ( not self.controls:IsControlActive("cycle") and self.was_cycle_key_pressed ) then
    self.was_cycle_key_pressed = false
  end
  
  local weapon = self.weapons[self.current_weapon]
  
  -- Aim down sights
  local aim_down_sights_pressed = self.controls:IsControlActive("aim")
  if ( aim_down_sights_pressed and not self.was_aim_down_sights_pressed ) then
    self.aim_down_sights = not self.aim_down_sights
    self.was_aim_down_sights_pressed = true
    if ( self.aim_down_sights ) then self.running = false end
  elseif ( not aim_down_sights_pressed and  self.was_aim_down_sights_pressed ) then
     self.was_aim_down_sights_pressed = false
  end
  weapon:SetAimDownSights(self.aim_down_sights)
  
  -- Fire the weapon
  self.time_since_last_fire = self.time_since_last_fire + delta_time
  
  local fire_pressed = self.controls:IsControlActive("fire")
  if ( weapon.is_automatic and fire_pressed ) then
    if ( self.time_since_last_fire > (1 / weapon.fire_speed) ) then
      self.time_since_last_fire = 0
      weapon:Fire()
    end
  else
    if fire_pressed and not self.was_fire_pressed then
      self.was_fire_pressed = true
      weapon:Fire()
    elseif not fire_pressed and self.was_fire_pressed then
      self.was_fire_pressed = false
    end
  end

  -- Update the weapons
  for i = 1, self.num_weapons do
    self.weapons[i]:Update(update_info)
    self.weapons[i]:SetPosition(center_of_mass)
  end
  
  
  self.bob_tick = self.bob_tick + self.bob_speed * delta_time
  
  if ( self.is_on_ground ) then
    self.bob_y = math.sin(self.bob_tick) * 0.075
  end
  
  
  -- Update the HUD
  self.hud:Update(update_info)
end

function Player:Render(render_info)
  local delta_time = render_info.delta_time:Seconds()
  
  
  
  self.camera:SetPosition(Vector.AddFVec3(self.position, FVec3(0, self.bob_y, 0)))
  self.camera:Update()
  
  
  local rotation_fix = self.camera:GetRotation()
  rotation_fix.y = -rotation_fix.y;
  
  local weapon_rotation = self.weapons[self.current_weapon]:GetCameraRotation()
  local weapon_translation = self.weapons[self.current_weapon]:GetCameraTranslation()
  local camera_rotation = Matrix.InverseFMat4(self.camera:GetViewMatrix())
  local weapon_transform = Matrix.MultiplyFMat4(Matrix.MultiplyFMat4(camera_rotation, weapon_translation), weapon_rotation)
  
  self.weapons[self.current_weapon].mesh:SetModelMatrix(weapon_transform)
  self.weapons[self.current_weapon]:Render(render_info, self.level)
  
  -- Render the HUD
  self.hud:Render(render_info)
end


function Player:__new(level)
  self:Init(level)
  
  
  
  self.camera = PerspectiveCamera(1.66, 60, 0.01, 1000)
  self.position = FVec3(0, 1.5, 0)
  self.hud = HUD:new(self)
  self.controls = Controls:new()
  
  
  self.mass = 70
  self.radius = 0.2
  self.height = 1.8
  self.speed = 5
  self.base_bob_speed = 10
  self.bob_speed = self.base_bob_speed
  self.bob_tick = 0
  self.bob_y = 0
  self.running = false
  self.is_on_ground = true
  
  self.rig = HumanRig:new("Lucas", level.game.models_folder .. "/Lucas/Lucas.dae") 
  self.collision_shape = CapsuleCollisionShape(self.radius, self.height / 1.5)
  self.rigid_body = RigidBody(self.collision_shape, self.mass)
  self.rigid_body:SetAngularFactor(FVec3(0, 0, 0))
  self.rigid_body:SetPosition(FVec3(0, self.height / 2 + 0.1, 0))
  self.level.scene:GetPhysicsWorld():AddRigidBody(self.rigid_body)
  
  self.weapons = {}
  self:SetWeapon(1, Colt:new(level))
  self:SetWeapon(2, AK47:new(level))
  self:SetWeapon(3, Katana:new(level))
  self.current_weapon = 1
  self.num_weapons = 3
  self.aim_down_sights = false
  self.was_cycle_key_pressed = false
  self.was_fire_pressed = false
  self.was_aim_down_sights_pressed = false
  self.time_since_last_fire = 0
  
  self.scene_object:AddUpdateFunction(MemberFunctionCallback(self, self.Update))
  self.scene_object:AddRenderFunction(MemberFunctionCallback(self, self.Render))
  
  
end


return Player

