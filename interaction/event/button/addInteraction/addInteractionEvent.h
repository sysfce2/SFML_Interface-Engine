#pragma once
#include "../simple/buttonEventSimple.h"
#include "../../../interactionManager/interactionManager.h"

namespace ui {
	class AddInteractionEvent : public ButtonEvent_Simple {
	protected:
		IInteraction* interaction;
		InteractionManager* interactionManager;
		
		void startPressed(sf::Vector2i windowPosition) override;
		
		void stopPressed (sf::Vector2i windowPosition) override;
		
		void whilePressed(sf::Vector2i windowPosition) override;
		
		void notPressed  (sf::Vector2i windowPosition) override;
		
		void copy(AddInteractionEvent* addInteractionEvent);
		
	public:
		explicit AddInteractionEvent(IInteraction& interaction);
		
		void init(InteractionManager &interactionManager);
		
		void setInteraction(IInteraction& interaction);
		
		AddInteractionEvent* copy() override;
	};
}
