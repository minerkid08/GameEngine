#include "ProfilingLayer.h"
#include <list>
namespace Engine{
	ProfilingLayer::ProfilingLayer() : Layer("ProfilingLayer"){
	}
	void ProfilingLayer::imGuiRender(){

		float current = timer.getTime();
		times.insert(times.begin(), 1, current);
		if(times.size() > 100){
			times.pop_back();
		}
		timer.reset();
		float a[times.size()];
		int count = times.size()-1;
		float min = 9999;
		float max = -1;
		for(float t : times){
			a[count] = t;
			count--;
			if(t > max){
				max = t;
			}
			if(t < min){
				min = t;
			}
		}
		ImGui::Begin("Time");
		ImGui::PlotLines("Update Loop", a, times.size());
		ImGui::Text(("Min: " + std::to_string(min) + ", Max: " + std::to_string(max) + ", Current: " + std::to_string(current)).c_str());
		ImGui::End();
	}
}