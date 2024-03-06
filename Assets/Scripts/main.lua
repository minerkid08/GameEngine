local cells = {};

local board = {};
local playerGrid = {};

local bCount = 7;

local spriteTable = {};

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

local function updateCell(x, y)
	---@type SpriteRenderer
	local renderer = cells[x][y];
	local spriteX = spriteTable[playerGrid[x][y]][2];
	local spriteY = spriteTable[playerGrid[x][y]][1];
	renderer:setUV(0, {x = spriteX, y = spriteY});
	renderer:setUV(1, {x = spriteX + 0.25, y = spriteY});
	renderer:setUV(2, {x = spriteX + 0.25, y = spriteY + 0.25});
	renderer:setUV(3, {x = spriteX, y = spriteY + 0.25});
end

local function updateZero(x, y)
	for x2 = -1, 1 do
		for y2 = -1, 1 do
			local mx = x + x2;
			local my = y + y2;
			if(mx >= 0 and mx < 8 and my >= 0 and my < 4) then
				if(playerGrid[mx][my] == -2) then
					playerGrid[mx][my] = board[mx][my];
					updateCell(mx, my);
					if(playerGrid[mx][my] == 0) then
						updateZero(mx, my);
					end
				end
			end
		end
	end
end

local function newGame()
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

	local found = false;
	for x = 0, 7 do
		for y = 0, 3 do
			if(board[x][y] == 0 and not found) then
				playerGrid[x][y] = 0;
				updateZero(x, y);
				found = true;
			end
			updateCell(x, y);
		end
	end
end

function create()
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
			renderer:setTint({r = 1, g = 1, b = 1, a = 1});
			cells[x][y] = renderer;
		end
	end
	newGame();
end

local keys = {};

function update(deltaTime)
	if(Input.keyDown(Keycodes.r) and not keys.r) then
		keys.r = true;
		newGame();
	elseif(not Input.keyDown(Keycodes.r)) then
		keys.r = false;
	end
	if(Input.mouseDown(0) and not keys.lmb) then
		local playerX = math.floor(Input:mouseX() / World.getWindowWidth() * 8);
		local playerY = math.floor(Input:mouseY() / World.getWindowHeight() * 4);
		if(playerX < 0 or playerX > 7 or playerY < 0 or playerY > 7) then
			return;
		end
		keys.lmb = true;
		if(playerGrid[playerX][playerY] >= -3) then
			playerGrid[playerX][playerY] = board[playerX][playerY];
			updateCell(playerX, playerY);
			if(playerGrid[playerX][playerY] == 0) then
				updateZero(playerX, playerY);
			end
		end
	elseif(not Input.mouseDown(0)) then
		keys.lmb = false;
	end

	if(Input.mouseDown(1) and not keys.rmb) then
		local playerX = math.floor(Input:mouseX() / World.getWindowWidth() * 8);
		local playerY = math.floor(Input:mouseY() / World.getWindowHeight() * 4);
		if(playerX < 0 or playerX > 7 or playerY < 0 or playerY > 7) then
			return;
		end
		keys.rmb = true;
		if(playerGrid[playerX][playerY] <= -1) then
			if(playerGrid[playerX][playerY] == -2) then
				playerGrid[playerX][playerY] = -3;
			else
				playerGrid[playerX][playerY] = -2;
			end
			updateCell(playerX, playerY);
		end
	elseif(not Input.mouseDown(1)) then
		keys.rmb = false;
	end
end