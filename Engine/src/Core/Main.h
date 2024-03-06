#pragma once
#include "Log.h"
#include "App.h"
#include "Args.h"

extern Engine::App* Engine::createApp();
int main(int argc, const char** argv){
	
	Args::argc = argc;
	Args::argv = argv;

	Engine::App* app = Engine::createApp();
	app->run();
	delete app;
}