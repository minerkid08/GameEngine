#include "ProfilingLayer.h"
#include <list>
namespace Engine{
	ProfilingLayer::ProfilingLayer() : Layer("ProfilingLayer"){
		
	}
	void ProfilingLayer::imGuiRender(){
		times.insert(times.begin(), 1, timer.getTime());
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
		//ImGui::Text("Min: %d, Max: %d", min, max);
		ImGui::End();
	}
}