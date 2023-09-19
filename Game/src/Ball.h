#pragma once

#include "Paddle.h"

class Ball{
	public:
	glm::vec2 position;
	glm::vec2 velocity;
	int size;
	int screenHeight;
	int screenWidth;
	int lscore;
	int rscore;
	int speed;
	Engine::Transform transform;
	Engine::shdPtr<Engine::Texture2D> tex;
	Ball();
	void update();
	void collidePaddle(Paddle* paddle);
	void draw();
	void reset();
	void resetScore();
};