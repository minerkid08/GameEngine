local t2;
local renderer;
function create()
    info("create");
    local ent = Entity:getWithName("ent2");
    t2 = ent:getComp("transform");

    renderer = entity:getComp("spriteRenderer");
end

function update(deltaTime)
    local pos = transform:getPos();
    local angle = transform:getRot();
    if(Input.keyDown(Keycodes.w)) then
        pos.y = pos.y + deltaTime;
    end
    if(Input.keyDown(Keycodes.s)) then
        pos.y = pos.y - deltaTime;
    end
    if(Input.keyDown(Keycodes.d)) then
        pos.x = pos.x + deltaTime;
    end
    if(Input.keyDown(Keycodes.a)) then
        pos.x = pos.x - deltaTime;
    end
    if(Input.keyDown(Keycodes.q)) then
        angle = angle + deltaTime * 5;
    end
    if(Input.keyDown(Keycodes.e)) then
        angle = angle - deltaTime * 5;
    end
    transform:setPos(pos);
    transform:setRot(angle);
    local x = math.sin(-angle) * 0.5 + pos.x;
    local y = math.cos(-angle) * 0.5 + pos.y;
    t2:setPos({x = x, y = y});
    t2:setRot(angle);

    local color = renderer:getTint();
    if(Input.keyDown(Keycodes.u) and color.r < 1) then
        color.r = color.r + deltaTime;
    end
    if(Input.keyDown(Keycodes.j) and color.r > 0) then
        color.r = color.r - deltaTime;
    end

    if(Input.keyDown(Keycodes.i) and color.g < 1) then
        color.g = color.g + deltaTime;
    end
    if(Input.keyDown(Keycodes.k) and color.g > 0) then
        color.g = color.g - deltaTime;
    end

    if(Input.keyDown(Keycodes.o) and color.b < 1) then
        color.b = color.b + deltaTime;
    end
    if(Input.keyDown(Keycodes.l) and color.b > 0) then
        color.b = color.b - deltaTime;
    end

    if(Input.keyDown(Keycodes.p) and color.a < 1) then
        color.a = color.a + deltaTime;
    end
    if(Input.keyDown(Keycodes.semicolon) and color.a > 0) then
        color.a = color.a - deltaTime;
    end

    renderer:setTint(color);
end

function destroy()
    info("destroy");
end