transform = nil;
---@type Transform
local src = nil;
---@type Vec2
local srcPos = nil;
---@type Transform
local dest = nil;
---@type Vec2
local destPos = nil;

local velStep = 0.05;

function create()
    transform = entity:getComp("transform");
    src = Entity:getWithName("src"):getComp("transform");
    dest = Entity:getWithName("dest"):getComp("transform");
    destPos = Vec2.new();
end

function update()
    srcPos = Vec2.new();
    if(Input.keyDown(Keycodes.w)) then
        srcPos.y = 1;
    end
    if(Input.keyDown(Keycodes.s)) then
        srcPos.y = -1;
    end
    if(Input.keyDown(Keycodes.a)) then
        srcPos.x = 1;
    end
    if(Input.keyDown(Keycodes.d)) then
        srcPos.x = -1;
    end
    destPos = velocity({x = 0, y = 0}, srcPos);
    
    dest.pos:setX(destPos.x);
    dest.pos:setY(destPos.y);
    src.pos:setX(srcPos.x);
    src.pos:setY(srcPos.y);
end

function velocity(target, start)
    if(Vec2.dist(start, target) < velStep) then 
        return target;
    end
    local a = Vec2.sub(target, start);
    local b = Vec2.div(a, Vec2.len(a));
    local c = Vec2.mul(b, velStep);
    local d = Vec2.add(c, start);
    return d;
end

    -- public Vec2 getVel(Vec2 target, Vec2 start, float velStep){
    --     if(start.sub(target).length() < velStep){return target;}
    --     Vec2 a = target.sub(start);
    --     Vec2 b = a.div(new Vec2(a.neg().length()));
    --     Vec2 c = b.mul(new Vec2(velStep));
    --     Vec2 d = c.add(start);
    --     return d;
    -- }