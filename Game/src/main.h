#include <iostream>
#include <Engine.h>
#include <math.h>
#include "Ball.h"
#include "Paddle.h"

class Pong : public Engine::Layer{
	public:
	bool paused = true;
	const int screenWidth = 800;
	const int screenHeight = 800;
	Ball* ball;
	Paddle* player;
	Paddle* paddle2;
	bool prevSpace;
	Engine::Camera cam;
	Engine::Transform bg;
	float aspect = 1280.0f/720.0f;
	float zoom = 0.5f;
	bool resize = true;
	Pong(){
		ball = new Ball();
		ball->size = 8;
		ball->screenHeight = screenHeight;
		ball->screenWidth = screenWidth;
		ball->position = {screenWidth/2.0f, screenHeight/2.0f};
		ball->transform.scale = {16.0f / screenWidth, 16.0f / screenHeight};
		ball->velocity = {5,5};
		ball->reset();
		ball->resetScore();

		player = new Paddle();
		player->position = {10,ball->position.y - (ball->size * 3)};
		player->size = {10,80};
		player->screenHeight = screenHeight;
		player->screenWidth = screenWidth;

		paddle2 = new Paddle();
		paddle2->position = {780,1};
		paddle2->size = {10,80};
		paddle2->screenHeight = screenHeight;
		paddle2->screenWidth = screenWidth;

		cam.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
		bg.pos.z = -0.1f;
		ImGui::GetStyle().ScaleAllSizes(2.0f);
	}
	~Pong(){
		delete player;
		delete ball;
		delete paddle2;
	}
	void imGuiRender(){
		ImGui::Begin("score");
		ImGui::Text(("left: " + std::to_string(ball->lscore)).c_str());
		ImGui::Text(("right: " + std::to_string(ball->rscore)).c_str());
		ImGui::End();
	}
	void update(float deltaTime){
		if(!paused){
			if(Engine::Input::keyDown(EngineKeycode_UP)){
				player->position.y += 1000 * deltaTime;
			}
			if(Engine::Input::keyDown(EngineKeycode_DOWN)){
				player->position.y -= 1000 * deltaTime;
			}
			player->clampPosition();

			paddle2->update(ball);
			paddle2->clampPosition();

			if(player->collide(ball))
				ball->collidePaddle(player);
			if(paddle2->collide(ball))
				ball->collidePaddle(paddle2);

			ball->update();
		}
		Engine::Renderer2D::beginScene(cam);
		
		//string text = to_string((int)ball->lscore) + ":" + to_string((int)ball->rscore);
		//const char *text2 = text.c_str();
		//DrawText(text2, screenWidth/2-40, screenHeight/2-40, 80, WHITE);
		Engine::Renderer2D::draw(bg, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		ball->draw();
		player->draw();
		paddle2->draw();
		Engine::Renderer2D::endScene();
	}
	bool windowResize(Engine::WindowResizeEvent* e){
		aspect = (float)e->width/(float)e->height;
		cam.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
		return false;
	}
	bool keyDown(Engine::KeyDownEvent* e){
		if(e->keyCode == EngineKeycode_SPACE){
			paused = !paused;
		}
		return false;
	}
	void event(Engine::Event* e){
		Engine::EventDispatcher d(e);
		d.dispatch<Engine::WindowResizeEvent>(BindFn(windowResize));
		d.dispatch<Engine::KeyDownEvent>(BindFn(keyDown));
	}
};