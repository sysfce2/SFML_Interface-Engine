#pragma once

#include "../../../../../../../../interaction/event/wheel/simple/wheelEventSimple.hpp"

namespace ui {
	class BaseSlider;
	
	class SliderWheelEvent : public WheelEvent_Simple {
	public:
		enum class Relativity {
			relationArea,
			relationSlider
		};
	
		explicit SliderWheelEvent(BaseSlider& slider, bool horizontal = false, Relativity relativity = Relativity::relationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
		
		void setSlider(BaseSlider& slider);
		
		void startPressed(sf::Vector2i mousePosition, int value) override;
		
		void stopPressed(sf::Vector2i mousePosition, int value) override;
		
		void whilePressed(sf::Vector2i mousePosition, int value) override;
		
		void whileNotPressed(sf::Vector2i mousePosition, int value) override;
		
		SliderWheelEvent* copy() override;
		
	protected:
		BaseSlider* slider;
		sf::Vector2f sensitivity;
		bool horizontal;
		bool relativity;
	};
	
	template<>
	struct Decode<SliderWheelEvent::Relativity> {
		static bool decode(const YAML::Node& node, SliderWheelEvent::Relativity& relativity);
	};
}