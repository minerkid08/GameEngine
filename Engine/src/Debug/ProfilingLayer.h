#include "Core/Layer.h"
#include "Core/Timer.h"
#include "imgui/imgui.h"
#include <windows.h>
namespace Engine{
	class API ProfilingLayer : public Layer{
		public:
		ProfilingLayer();
		void imGuiRender();
		private:
		Timer timer;
		std::vector<float> times;
	};
}