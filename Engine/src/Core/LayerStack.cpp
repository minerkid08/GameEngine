#include "LayerStack.h"

namespace Engine{
	LayerStack::LayerStack(){}
	LayerStack::~LayerStack(){
		for(Layer* layer : layers){
			delete layer;
		}
	}
	void LayerStack::pushLayer(Layer* layer){
		layers.emplace(layers.begin() + insert, layer);
		insert++;
		layer->attach();
	}
	void LayerStack::popLayer(Layer* layer){
		auto it = std::find(layers.begin(), layers.end(), layer);
		if(it != layers.end()){
			layers.erase(it);
			layer->detach();
			insert--;
		}
	}
	void LayerStack::pushOverlay(Layer* overlay){
		layers.emplace_back(overlay);
		overlay->attach();
	}
	void LayerStack::popOverlay(Layer* overlay){
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if(it != layers.end()){
			layers.erase(it);
			overlay->detach();
		}
	}
};