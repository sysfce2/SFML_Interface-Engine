#include "interactiveSimple.hpp"

namespace ui {
	Interactive_Simple::Interactive_Simple(BoxPtr<IInteraction>&& interaction) :
		interact(false), oldInteract(false), interaction(std::move(interaction)){
	}
	
	void Interactive_Simple::init(InteractiveInitInfo interactiveInitInfo) {
		interactiveInitInfo.updateManager.add(*this);
		interaction->init({interactiveInitInfo.toGeneral(*interactionManager, *interactionStack)});
	}
	
	void Interactive_Simple::update() {
		if(interact != oldInteract) {
			oldInteract = interact;
			if(interact) {
				interactionManager->addInteraction(*interaction);
			} else {
				interactionManager->deleteInteraction(*interaction);
			}
		}
		interact = false;
	}
	
	bool Interactive_Simple::updateInteractions(sf::Vector2f) {
		interact = true;
		return true;
	}
}
