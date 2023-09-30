#include "Components.h"
#include "ScriptableObject.h"

namespace Engine{
	namespace Components{
		void NativeScript::reset(){
			destroy();
			enabled = true;
			path = "";
		}
	}
}