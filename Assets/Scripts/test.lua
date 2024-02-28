---@type SpriteRenderer
local renderer = nil;

function create()
	renderer = entity:getComp("spriteRenderer");
	local renderer2 = Entity:getWithName("ent2"):getComp("spriteRenderer");
	renderer2:setTex(renderer:getTex());
end

function update(deltaTime)
end