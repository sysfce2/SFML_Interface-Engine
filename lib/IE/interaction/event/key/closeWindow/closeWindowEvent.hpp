#pragma once

#include "../simple/keyEventSimple.hpp"
#include "modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {
	class CloseWindowEvent : public KeyEvent_Simple {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
	public:
		CloseWindowEvent();
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		KeyEvent* copy() override;
	
	protected:
		sf::RenderWindow* window;
	};
	
	template<>
	struct DecodePointer<CloseWindowEvent> {
		static bool decodePointer(const YAML::Node&, CloseWindowEvent*& closeWindowEvent);
	};
}