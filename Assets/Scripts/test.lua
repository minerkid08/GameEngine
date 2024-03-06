local mouseDown = false;

function update(deltaTime)
	if(Input.mouseDown(0) and not mouseDown) then
		mouseDown = true;
		local x = Input.mouseX() / World.getWindowWidth();
		local y = Input.mouseY() / World.getWindowHeight();
		info(tostring(x) .. ", " .. tostring(y));
	elseif(not Input.mouseDown(0)) then
		mouseDown = false;
	end
end