#pragma once
#include "Core.h"
#include "Layer.h"

namespace Engine{
	class LayerStack{
		public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin(){return layers.begin();}
		std::vector<Layer*>::iterator end(){return layers.end();}
		private:
		std::vector<Layer*> layers;
		unsigned int insert = 0;
	};
}