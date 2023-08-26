#include <chrono>

namespace Engine{
	class Timer{
		public:
		Timer(){
			startTime = std::chrono::high_resolution_clock::now();
		}
		void reset(){
			startTime = std::chrono::high_resolution_clock::now();
		}
		float getTime(){
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> t = endTime - startTime;
			return t.count() * 0.001f;
		}
		private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	};
}