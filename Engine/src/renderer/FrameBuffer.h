#pragma once
#include "Core/Core.h"
namespace Engine{
	struct FrameBufferSpec{
		int width = 1280;
		int height = 720;
		int samples = 1;
		bool swapChainTarget = false;
	};
	class API FrameBuffer{
		public:
		FrameBuffer(const FrameBufferSpec& _spec);
		~FrameBuffer();
		FrameBufferSpec getSpec(){return spec;}
		void regen(const FrameBufferSpec& _spec);
		void bind();
		void unbind();
		uint32_t getColor(){return color;}
		private:
		FrameBufferSpec spec;
		uint32_t id;
		uint32_t color;
		uint32_t depth;
	};
}