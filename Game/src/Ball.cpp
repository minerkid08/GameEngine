#include "ball.h"
#include "Paddle.h"
#include <iostream>

Ball::Ball(){
	resetScore();
	speed = 10;
	tex = std::make_shared<Engine::Texture2D>("Game/textures/ball.png");
}

void Ball::collidePaddle(Paddle* paddle){

	float factor = -(paddle->position.y - position.y)-paddle->size.y/2;
	factor = factor / (paddle->size.y / 2) * (5 * 3.14 / 12);
	velocity = {speed*-cos(factor), speed*sin(factor)};
	if(paddle->position.x == 10){
		//score++;
		velocity.x *= -1;
	}
}
void Ball::draw(){
	transform.pos.x = (position.x - screenWidth/2.0f)/(screenWidth);
	transform.pos.y = (position.y - screenHeight/2.0f)/(screenHeight);
	//Engine::Log::Info(std::to_string(transform.pos.x) + " " + std::to_string(transform.pos.y));
	Engine::Renderer2D::draw(transform, tex);
}
void Ball::update(){
	if(position.y + size >= screenHeight){
		velocity.y *= -1;
	}
	if(position.y - size <= 0){
		velocity.y *= -1;
	}

	if(position.x + size >= screenWidth){
		reset();
		lscore++;
	}
	if(position.x - size <= 0){
		reset();
		rscore++;
	}

	position.x += velocity.x;
	position.y += velocity.y;
}
void Ball::reset(){
	position = {screenWidth/2.0f, screenHeight/2.0f};
	velocity = {5,0};
}
void Ball::resetScore(){
	lscore = 0;
	rscore = 0;
}