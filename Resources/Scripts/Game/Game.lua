
-- Load modules
local Class = Class or require("Scripts.Class")
local MainMenu = MainMenu or require("Scripts.Game.Menu.MainMenu")
local LevelRegistry = LevelRegistry or require("Scripts.Game.Level.LevelRegistry")

Game = Class:new()




function Game:Start()
  
  --Engine:LockUPS(256)
  
  -- Set up the Display
  Display:SetClearColor(0.1, 0.1, 0.5, 1)
  Display:Maximize()
  Display:CaptureMouse(true)
  
  -- Set up the game
  self.level = LevelRegistry["Level_SuburbanTown"]:new(self)
  Display:SetTitle("ShooterGame v0.1 - " .. self.level.name)
end


function Game:Update(update_info)
  
end

function Game:Render(render_info)
  
end


-- Constructor
function Game:__new()
  
  self.shaders_folder = Engine:GetPlatform():GetGameFolder() .. "/Shaders"
  self.levels_folder = Engine:GetPlatform():GetGameFolder() .. "/Levels"
  self.models_folder = Engine:GetPlatform():GetGameFolder() .. "/Models"
  
  self.main_menu = nil
  self.level = nil
  
  
  
  
  
  
  
end





return Game

