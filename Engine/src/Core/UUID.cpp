#include "UUID.h"
#include <random>
namespace Engine{
	static std::random_device rand;
	static std::mt19937_64 engine(rand());
	static std::uniform_int_distribution<uint64_t> dist;
	UUID::UUID(){
		id = dist(engine);
	}
	UUID::UUID(uint64_t _id){
		id = _id;
	}
}