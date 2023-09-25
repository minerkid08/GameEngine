#pragma once
#include "Core/Core.h"
#include "Scene.h"
#include <json/json.hpp>
namespace Engine{
	class API Serializer{
		public:
		Serializer(){}
		void setEnt(const shdPtr<Scene>& _scene){scene = _scene;}
		void seralize(const std::string& path);
		void deseralize(const std::string& path);
		private:
		using json = nlohmann::json;
		shdPtr<Scene> scene;
		void seralizeEnt(json& out, Entity& ent);
	};
}