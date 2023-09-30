#pragma once
#include <Engine.h>
#include <json/json.hpp>
namespace Engine{
	class Serializer{
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