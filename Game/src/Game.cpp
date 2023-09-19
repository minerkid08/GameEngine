#include <Engine.h>
#include <Core/Main.h>

#include "main.h"
#include "2dLayer.h"
class Game : public Engine::App {
	public:
	Game() : Engine::App(100, 100, "not a window.png"){
		pushLayer(new Engine::ProfilingLayer());
		pushLayer(new Layer2D());
	}
};
Engine::App* Engine::createApp(){
	return new Game();
}