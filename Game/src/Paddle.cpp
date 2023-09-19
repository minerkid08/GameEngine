#include "Paddle.h"
#include "Ball.h"
#include <math.h>

bool Paddle::collide(Ball* ball){
	if(position.x == 10){
		if(ball->position.x < position.x - size.x){
			return false;
		}
	}else{
		if(ball->position.x > position.x){
			return false;
		}
	}
	return(
		ball->position.x < position.x + size.x &&
    	ball->position.x + ball->size > position.x &&
    	ball->position.y < position.y + size.y &&
    	ball->position.y + ball->position.y > position.y
	);
}
void Paddle::draw(){
	transform.pos.x = (position.x + (size.x/2.0f) - screenWidth/2.0f)/(screenWidth);
	transform.pos.y = (position.y + (size.y/2.0f) - screenHeight/2.0f)/(screenHeight);
	transform.scale = {size.x / screenHeight, size.y / screenWidth};
	Engine::Renderer2D::draw(transform, glm::vec4(1.0f));
}
void Paddle::clampPosition(){
	if(position.y < 0){
		position.y = 0;
	}
	if(position.y + size.y > screenHeight){
		position.y = screenHeight - size.y;
	}
}
void Paddle::update(Ball* ball){
	if(ball->position.y < position.y - 30){
		position.y -= 10;
	}
	if(ball->position.y > position.y + size.y + 30){
		position.y += 10;
	}
	if(ball->position.y < position.y + 10){
		position.y -= 5;
	}
	if(ball->position.y > position.y + size.y - 10){
		position.y += 5;
	}
}