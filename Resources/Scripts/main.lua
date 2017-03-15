

local Game = require("Scripts.Game.Game")


game = Game:new(game)
game:Start()


print = LogMessage

function Update(update_info)
  game:Update(update_info)
end

function Render(render_info)
  game:Render(render_info)
end


