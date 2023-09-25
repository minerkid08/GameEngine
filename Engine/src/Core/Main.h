#pragma once
#include "Log.h"
#include "App.h"
extern Engine::App* Engine::createApp();
int main(){
	Engine::App* app = Engine::createApp();
	app->run();
	delete app;
}