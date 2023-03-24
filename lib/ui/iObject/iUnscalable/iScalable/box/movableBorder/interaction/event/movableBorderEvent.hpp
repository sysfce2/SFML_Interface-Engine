#pragma once

#include "../../../../../../../interaction/event/key/simple/keyEventSimple.hpp"

namespace ui {
	class BoxWithMovableBorder;
	
	class MovableBorderEvent : public KeyEvent_Simple {
	protected:
		BoxWithMovableBorder *box;
		sf::Vector2i startMousePosition;
		float startBorderValue;
		bool active;
		
		void copy(MovableBorderEvent *event);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit MovableBorderEvent(BoxWithMovableBorder &box);
		
		void setBox(BoxWithMovableBorder &box);
		
		MovableBorderEvent *copy() override;
	};
}



