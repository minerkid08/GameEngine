#pragma once

#include <Engine.h>

class Ball;

class Paddle{
	public:
	glm::vec2 position;
	glm::vec2 size;
	int screenWidth;
	int screenHeight;
	Engine::Transform transform;
	void draw();
	bool collide(Ball* ball);
	void clampPosition();
	void update(Ball* ball);
};