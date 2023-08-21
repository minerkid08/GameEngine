#pragma once

namespace Engine{
	class Time{
		public:
		Time(float time){
			deltaTime = time;
		}
		operator float() {return deltaTime;}
		float getSec(){return deltaTime;}
		float getMil(){return deltaTime * 1000;}
		private:
		float deltaTime = 0;
	};
}