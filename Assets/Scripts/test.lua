---@type SpriteRenderer
local renderer = nil;

function create()
	renderer = entity:getComp("spriteRenderer");
	info("a");
	renderer:setUV(2, {x = 1, y = 1});
	info("b");
	renderer:setUV(3, {x = 0, y = 1});
end

function update(deltaTime)
end