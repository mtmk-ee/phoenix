
local Class = Class or require("Scripts.Class")
local Level = Level or require("Scripts.Game.Level.Level")
local Entity = Entity or require("Scripts.Game.Level.Entities.Entity")
local Player = Player or require("Scripts.Game.Level.Entities.Player")
local Enemy = Enemy or require("Scripts.Game.Level.Entities.Enemy")


Level_SuburbanTown = Class:new(Level)


function Level_SuburbanTown:LoadSkybox()
  local skybox_texture_folder = self.level_models_folder .. "/Skybox"
  local skybox_texture_info = CubemapTextureInfo()
  skybox_texture_info.posx_path = skybox_texture_folder .. "/posx.png"
  skybox_texture_info.negx_path = skybox_texture_folder .. "/negx.png"
  skybox_texture_info.posy_path = skybox_texture_folder .. "/posy.png"
  skybox_texture_info.negy_path = skybox_texture_folder .. "/negy.png"
  skybox_texture_info.posz_path = skybox_texture_folder .. "/posz.png"
  skybox_texture_info.negz_path = skybox_texture_folder .. "/negz.png"
  
  self.skybox_texture = CubemapTexture.Load(skybox_texture_info)
  self.skybox = Skybox(self.skybox_texture, 2.0)
  
  self.skybox_shader = ShaderProgram()
  local vert_shader = ShaderSource.Load(self.shaders_folder .. "/Level_SuburbanTown/Skybox/Skybox.vert", 0)
  local frag_shader = ShaderSource.Load(self.shaders_folder .. "/Level_SuburbanTown/Skybox/Skybox.frag", 1)
  self.skybox_shader:AttachShader(vert_shader)
  self.skybox_shader:AttachShader(frag_shader)
  self.skybox_shader:LinkProgram()
end

function Level_SuburbanTown:GetPlayer()
  return self.entities["Player"]
end

function Level_SuburbanTown:Update(update_info)
  local player = self.entities["Player"]
  
  -- Reset player if they fell off the map
  if ( player:GetPosition().y < -20 ) then
    player:SetPosition(FVec3(0, player.height / 2, 0))
    player:SetVelocity(FVec3(0, 0, 0))
    local camera_rotation = player.camera:GetRotation()
    camera_rotation.x = 0
    player.camera:SetRotation(camera_rotation)
  end
  
  
end

function Level_SuburbanTown:Render(render_info)
  local player = self.entities["Player"]
  
  -- Render skybox
  self.skybox:Render(player.camera, self.skybox_shader)
  
  -- Render player
  self.level_model:GetShaderProgram():UseProgram()
  self.level_model:GetShaderProgram():SetUniformFloat("ambient_intensity", 0.25)
  self.level_model:GetShaderProgram():SetUniformFloat("diffuse_intensity", 1)
  self.level_model:GetShaderProgram():SetUniformFloat("specular_intensity", 0)
  self.level_model:GetShaderProgram():SetUniformFVec3("light_pos", self.light_position)
  self.level_model:Render(player.camera)
  
end


function Level_SuburbanTown:PopulateScene()
  self.entities = {}
  
  
  local player = Player:new(self)
  self.entities["Player"] = player
  
  --[[local num_enemies = 5
  for i = 0, num_enemies do
    local enemy = Enemy:new(self)
    local angle = 360 / num_enemies * i
    local position = FVec3(0, 0, 0)
    
    position.y = enemy.height / 2 + 0.1
    position.x = math.sin(angle * math.pi / 180) * 5
    position.z = math.cos(angle * math.pi / 180) * 5
    enemy:SetPosition(position)
    
    enemy.rotation.y = 90 - math.atan2(player.position.z - enemy.position.z, player.position.x - enemy.position.x) * 180 / math.pi
    
    self.entities["enemy" .. i] = enemy
    
  end]]--
  
end



function Level_SuburbanTown:__new(game)
  self:Init(game, "Level_SuburbanTown")
  self.light_position = Vector.MultFVec3(FVec3(-0.90047949552536, 0.35761293768883, -0.24748714268208), 500)
  self.light_camera = OrthoCamera(-10.0, 10.0, -10.0, 10.0, 1.0, 1000)
  
  
  self.level_folder = game.levels_folder .. "/Level_SuburbanTown"
  self.level_models_folder = Engine:GetPlatform():GetGameFolder() .. "/Models/Levels/Level_SuburbanTown"
  self.shaders_folder = Engine:GetPlatform():GetGameFolder() .. "/Shaders"
  self.scene = SceneManager:CreateScene()
  SceneManager:SetActiveScene(self.scene)
  
  self:PopulateScene()
  
  
  
  self.level_model = SkinnedMesh("Level_SuburbanTown")
  if ( not self.level_model:LoadMesh(self.game.models_folder .. "/Levels/Level_SuburbanTown/Level_SuburbanTown.obj") ) then
    print "Could not load level world model"
  else
    self.level_scale = FVec3(1.0, 1.0, 1.0)
    self.level_model:SetModelMatrix(Matrix.CreateScaleTransform(self.level_scale))
  end
  
  self.physics_world = self.scene:GetPhysicsWorld()
  
  self.gravity = FVec3(0, -12, 0)
  self.physics_world:SetGravity(self.gravity)
  
  self.level_collision_shape = MeshCollisionShape(self.level_model, self.level_scale)
  self.level_object = CollisionObject(self.level_collision_shape)
  self.level_object:SetFriction(0.0)
  self.physics_world:AddCollisionObject(self.level_object)
  
  self.ground_collision_shape = BoxCollisionShape(FVec3(47.5, 1, 47.5))
  self.ground_object = CollisionObject(self.ground_collision_shape)
  self.ground_object:SetPosition(FVec3(0, -0.6, 0))
  self.ground_object:SetFriction(0)
  self.physics_world:AddCollisionObject(self.ground_object)
  
  self:LoadSkybox()
  
  
  self.scene:AddUpdateFunction(MemberFunctionCallback(self, self.Update))
  self.scene:AddRenderFunction(MemberFunctionCallback(self, self.Render))
  
end
  

return Level_SuburbanTown

