#pragma once
#include <Engine.h>

namespace Engine{
	class SceneHierarchy{
		public:
		void setContext(const shdPtr<Scene>& _scene);
		void uiRender();
		private:
		void drawEntity(const Entity& ent);
		template<typename T> void drawComp(const char* name, ImGuiTreeNodeFlags flags, std::function<void(T&)> func, bool canDelete = true);
		shdPtr<Scene> scene;
		Entity selected;
	};
}