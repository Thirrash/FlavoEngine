#include "..\include\UserComponent.h"

Engine::BaseComponent::Family Engine::UserComponent::family() {
	static Family family = Engine::MAX_COMPONENTS - 1;
	return family;
}
