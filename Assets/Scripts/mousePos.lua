function create()
end

function update(deltaTime)
	if(Input.mouseDown(1)) then
		info(tostring(Input.mouseX()) .. ", " .. tostring(Input.mouseY()));
	end
end