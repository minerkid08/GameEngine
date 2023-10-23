moveState = 0;
scaleXState = 0;
scaleYState = 0;
transform = nil;
ent = nil;

function create()
	ent = Entity:getWithName("box");
	transform = ent:getComp("transform");
	transform.scale:setX(0.5);

	tag = ent:getComp("tag");
	info(tag:getTag());
	tag:setTag("box2");
end
function update(deltaTime)
	if(input.mouseDown(3)) then return end
	local x = transform.pos:getX();
	local y = transform.pos:getY();
	local r = transform:getRot();
	local w = transform.scale:getX();
	local h = transform.scale:getY();

	r = r + deltaTime;

	if(moveState == 0) then
		x = x + deltaTime;
		if(x > 1) then
			moveState = 1;
		end
	end
	if(moveState == 1) then
		y = y + deltaTime;
		if(y > 1) then
			moveState = 2;
		end
	end
	if(moveState == 2) then
		x = x - deltaTime;
		if(x < -1) then
			moveState = 3;
		end
	end
	if(moveState == 3) then
		y = y - deltaTime;
		if(y < -1) then
			moveState = 0;
		end
	end

	if(scaleXState == 0) then
		w = w - deltaTime * 0.75;
		if(w < -1) then
			scaleXState = 1;
		end
	end
	if(scaleXState == 1) then
		w = w + deltaTime * 0.75;
		if(w > 1) then
			scaleXState = 0;
		end
	end

	if(scaleYState == 0) then
		h = h - deltaTime * 0.75;
		if(h < -1) then
			scaleYState = 1;
		end
	end
	if(scaleYState == 1) then
		h = h + deltaTime * 0.75;
		if(h > 1) then
			scaleYState = 0;
		end
	end

	transform.pos:setX(x);
	transform.pos:setY(y);
	transform:setRot(r);
	transform.scale:setX(w);
	transform.scale:setY(h);
end