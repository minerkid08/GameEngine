#pragma once
#include <Engine.h>

namespace Engine{
	class SceneHierarchy{
		public:
		void setContext(const shdPtr<Scene>& _scene);
		void uiRender();
		bool getDrawCamera(){return drawFromSceneCamera;}
		private:
		bool drawFromSceneCamera = false;
		Entity selected;
		shdPtr<Scene> scene;
		void drawEntity(const Entity& ent);
		template<typename T> void drawComp(const char* name, ImGuiTreeNodeFlags flags, std::function<void(T&)> func, bool canDelete = true);
	};
}