#include <Engine.h>
#include <Core/Main.h>

#include "EditorLayer.h"
namespace Engine{
	class Editor : public App {
		public:
		Editor() : App(1280, 720, "Sisyphus the Editor"){
			pushLayer(new EditorLayer());
		}
	};
	App* createApp(){
		return new Editor();
	}
}