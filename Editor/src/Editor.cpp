#include <Engine.h>
#include <Core/Main.h>
#define lua_assert(x) std::cout << x << std::endl
#include "EditorLayer.h"
namespace Engine{
	class Editor : public App {
		public:
		Editor() : App(1280, 720, "Sisyphus the Editor", Window::WindowMode::FullscreenWindowed){
			pushLayer(new EditorLayer());
		}
	};
	App* createApp(){
		return new Editor();
	}
}