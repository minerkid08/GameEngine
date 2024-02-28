local cells = {};

local board = {};
local playerGrid = {};

local bCount = 5;

local spriteTable = {};

---@type Transform
local playerTransform;

spriteTable[-2] = {0.5,  0.75};
spriteTable[-1] = {0.5,  0.25};
spriteTable[0]  = {0.75, 0   };
spriteTable[-3] = {0.5,  0.5 };
spriteTable[1] 	= {0,    0   };
spriteTable[2] 	= {0,    0.25};
spriteTable[3] 	= {0,    0.5 };
spriteTable[4] 	= {0,    0.75};
spriteTable[5] 	= {0.25, 0   };
spriteTable[6] 	= {0.25, 0.25};
spriteTable[7] 	= {0.25, 0.5 };
spriteTable[8] 	= {0.25, 0.75};
spriteTable[9] 	= {0.5,  0   };

function create()
	playerTransform = Entity:getWithName("player"):getComp("transform");

	for x = 0, 7 do
		board[x] = {};
		playerGrid[x] = {};
		for y = 0, 3 do
			board[x][y] = 0;
			playerGrid[x][y] = -2;
		end
	end

	for i = 0, bCount-1 do
		local placed = false;
		while(not placed) do
			local x = math.random(0, 7);
			local y = math.random(0, 3);
			if(board[x][y] > -1) then
				board[x][y] = -1;
				placed = true;
			end
		end
	end
	
	for x = 0, 7 do
		for y = 0, 3 do
			local bombs = 0;
			if(board[x][y] == -1) then
				goto continue
			end
			for mx = -1, 1 do
				for my = -1, 1 do
					local x2 = x + mx;
					local y2 = y + my;
					if(x2 >= 0 and x2 < 8 and y2 >= 0 and y2 < 4) then
						if(board[x2][y2] == -1) then
							bombs = bombs + 1;
						end
					end
				end
			end
			board[x][y] = bombs;
		    ::continue::
		end
	end

	for x = 0, 7 do
		local found = false;
		for y = 0, 3 do
			if(board[x][y] == 0) then
				playerGrid[x][y] = 0;
				found = true;
				break;
			end
		end
		if(found) then
			break;
		end
	end

	---@type SpriteRenderer
	local renderer2 = entity:getComp("spriteRenderer");
	for x = 0, 7 do
		cells[x] = {};
		for y = 0, 3 do
			local ent = Entity:add("cell: " .. tostring(x) .. ", " .. tostring(y));
			---@type Transform
			local transform = ent:getComp("transform");
			transform:setPos({x = x, y = y, z = 0});
			---@type SpriteRenderer
			local renderer = ent:addComp("spriteRenderer");
			renderer:setMode("sprite");
			renderer:setTex(renderer2:getTex());
			
			local spriteX = spriteTable[playerGrid[x][y]][2];
			local spriteY = spriteTable[playerGrid[x][y]][1];

			renderer:setUV(0, {x = spriteX, y = spriteY});
			renderer:setUV(1, {x = spriteX + 0.25, y = spriteY});
			renderer:setUV(2, {x = spriteX + 0.25, y = spriteY + 0.25});
			renderer:setUV(3, {x = spriteX, y = spriteY + 0.25});
			renderer:setTint({r = 1, g = 1, b = 1, a = 1});
			cells[x][y] = renderer;
		end
	end
end

local keys = {};

local playerX = 0;
local playerY = 0;
function update(deltaTime)
	if(Input.keyDown(Keycodes.w) and not keys.w) then
		keys.w = true;
		playerY = playerY - 1;
		playerTransform:setPos({x = playerX, y = playerY, z = 1});
	elseif(not Input.keyDown(Keycodes.w)) then
		keys.w = false;
	end

	if(Input.keyDown(Keycodes.s) and not keys.s) then
		keys.s = true;
		playerY = playerY + 1;
		playerTransform:setPos({x = playerX, y = playerY, z = 1});
	elseif(not Input.keyDown(Keycodes.s)) then
		keys.s = false;
	end
	
	if(Input.keyDown(Keycodes.d) and not keys.d) then
		keys.d = true;
		playerX = playerX + 1;
		playerTransform:setPos({x = playerX, y = playerY, z = 1});
	elseif(not Input.keyDown(Keycodes.d)) then
		keys.d = false;
	end
	
	if(Input.keyDown(Keycodes.a) and not keys.a) then
		keys.a = true;
		playerX  = playerX - 1;
		playerTransform:setPos({x = playerX, y = playerY, z = 1});
	elseif(not Input.keyDown(Keycodes.a)) then
		keys.a = false;
	end
	
	if(Input.keyDown(Keycodes.e) and not keys.e) then
		keys.e = true;
		if(playerGrid[playerX][playerY] >= -3) then
			playerGrid[playerX][playerY] = board[playerX][playerY];
			---@type SpriteRenderer
			local renderer = cells[playerX][playerY];
			local spriteX = spriteTable[playerGrid[playerX][playerY]][2];
			local spriteY = spriteTable[playerGrid[playerX][playerY]][1];
			renderer:setUV(0, {x = spriteX, y = spriteY});
			renderer:setUV(1, {x = spriteX + 0.25, y = spriteY});
			renderer:setUV(2, {x = spriteX + 0.25, y = spriteY + 0.25});
			renderer:setUV(3, {x = spriteX, y = spriteY + 0.25});
		end
	elseif(not Input.keyDown(Keycodes.e)) then
		keys.e = false;
	end

	if(Input.keyDown(Keycodes.q) and not keys.q) then
		keys.q = true;
		if(playerGrid[playerX][playerY] < -1) then
			if(playerGrid[playerX][playerY] == -2) then
				playerGrid[playerX][playerY] = -3;
			else
				playerGrid[playerX][playerY] = -2;
			end
			---@type SpriteRenderer
			local renderer = cells[playerX][playerY];
			local spriteX = spriteTable[playerGrid[playerX][playerY]][2];
			local spriteY = spriteTable[playerGrid[playerX][playerY]][1];
			renderer:setUV(0, {x = spriteX, y = spriteY});
			renderer:setUV(1, {x = spriteX + 0.25, y = spriteY});
			renderer:setUV(2, {x = spriteX + 0.25, y = spriteY + 0.25});
			renderer:setUV(3, {x = spriteX, y = spriteY + 0.25});
		end
	elseif(not Input.keyDown(Keycodes.q)) then
		keys.q = false;
	end
end