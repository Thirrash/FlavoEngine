#include "Systems/UserSystem.h"
#include "UserComponent.h"
#include "Debug.h"

Engine::UserSystem::UserSystem(EntityManager& es) {
	ComponentHandle<UserComponent> userHandle;
	for (Entity entity : es.entities_with_components(userHandle)) {
		if (!userHandle.IsValid()) {
			continue;
		}

		userHandle.Get()->Start();
	}
}

Engine::UserSystem::~UserSystem() {

}

void Engine::UserSystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	ComponentHandle<UserComponent> userHandle;
	for (Entity entity : es.entities_with_components(userHandle)) {
		if (!userHandle.IsValid()) {
			continue;
		}

		userHandle.Get()->Update(dt);
	}
}
