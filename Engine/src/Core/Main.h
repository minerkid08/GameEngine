#pragma once
#include "Log.h"
#include "App.h"
extern Engine::App* Engine::createApp();
int main(){
	Engine::App* app = Engine::createApp();
	app->run();
	Engine::Log::Warn("warn");
	Engine::Log::Info("info");
	Engine::Log::Error("error");
	delete app;
}