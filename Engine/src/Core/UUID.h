#pragma once
#include "Core.h"
#include <unordered_map>
#include <stdint.h>
namespace Engine{
	class API UUID{
		public:
		UUID();
		UUID(uint64_t _id);
		UUID(const UUID&) = default;
		operator uint64_t() const {return id;}
		private:
		uint64_t id;
	};
}
namespace std{
	template<>
	struct hash<Engine::UUID>{
		std::size_t operator()(const Engine::UUID& uuid) const {
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}