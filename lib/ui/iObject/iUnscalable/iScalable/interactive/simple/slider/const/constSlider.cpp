#include <iostream>
#include "constSlider.hpp"

namespace ui {
	ConstSlider::ConstSlider(IUninteractive *slider, IUninteractive *background, const std::shared_ptr<WithCoefficientVec2> &value, float sliderScale, Key button, bool wheelHorizontal,
							 SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		BaseSlider(slider, background, value, new SliderInteraction{*this, button, wheelHorizontal, wheelRelativity, wheelSensitivity}), sliderScale(sliderScale) {
		
		sliderSize = slider->getNormalSize();
		aspectRatio = sliderSize.x / sliderSize.y;
	}
	
	ConstSlider::ConstSlider(IUninteractive *slider, IUninteractive *background, const std::shared_ptr<WithCoefficientVec2> &value, sf::Vector2i division, float sliderScale, Key button, bool wheelHorizontal) :
		BaseSlider(slider, background, value, new SliderInteraction{*this, button, division, wheelHorizontal}), sliderScale(sliderScale) {
		
		sliderSize = slider->getNormalSize();
		aspectRatio = sliderSize.x / sliderSize.y;
	}
	
	void ConstSlider::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		if(size.x / aspectRatio < size.y) {
			sliderSize = sf::Vector2f{size.x, size.x / aspectRatio} * sliderScale;
		} else {
			sliderSize = sf::Vector2f{size.y * aspectRatio, size.y} * sliderScale;
		}
		moveZoneSize = size - sliderSize;
		background->resize(size, position);
	}
	
	ConstSlider::ConstSlider(IUninteractive *slider, IUninteractive *background, const std::shared_ptr<WithCoefficientVec2> &value, SliderInteraction *interaction) :
		BaseSlider(slider, background, value, interaction) {
	}
	
	ConstSlider *ConstSlider::copy() {
		ConstSlider *constSlider{new ConstSlider{slider->copy(), background->copy(), value, dynamic_cast<SliderInteraction *>(interaction->copy())}};
		dynamic_cast<SliderInteraction *>(constSlider->interaction)->setSlider(*constSlider);
		BaseSlider::copy(constSlider);
		return constSlider;
	}
	
	bool convertPointer(const YAML::Node &node, ConstSlider *&constSlider) {
		IUninteractive *slider;
		IUninteractive *background;
		std::shared_ptr<WithCoefficientVec2> value;
		float sliderScale{1.0f};
		Key button{Key::mouseLeft};
		bool wheelHorizontal{false};
		
		node["slider"] >> slider;
		node["background"] >> background;
		value = Buffer::get<WithCoefficientVec2>(node["value"]);
		if(node["slider-scale"])
			node["slider-scale"] >> sliderScale;
		if(node["button"])
			node["button"] >> button;
		if(node["default-wheel"]) {
			wheelHorizontal = convertBool(node["default-wheel"], "horizontal", "vertical");
		}
		
		if(!node["division"]) {
			SliderWheelEvent::Relativity wheelRelativity{SliderWheelEvent::Relativity::relationArea};
			sf::Vector2f wheelSensitivity{0.2f, 0.2f};
			
			if(node["wheel-relativity"])
				node["wheel-relativity"] >> wheelRelativity;
			if(node["wheel-sensitivity"])
				node["wheel-sensitivity"] >> wheelSensitivity;
			
			{ constSlider = new ConstSlider{slider, background, value, sliderScale, button, wheelHorizontal, wheelRelativity, wheelSensitivity}; return true; }
		} else {
			sf::Vector2i division;
			
			node["division"] >> division;
			
			{ constSlider = new ConstSlider{slider, background, value, division, sliderScale, button, wheelHorizontal}; return true; }
		}
	}
}
