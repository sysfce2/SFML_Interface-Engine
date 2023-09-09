#include "Slider.hpp"

namespace ie {
	Slider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		const PSRVec2f& value,
		sf::Vector2f sliderScale,
		Key key,
		bool wheelHorizontal,
		SliderWheelAction::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(value),
		sliderScale(sliderScale),
		key(key),
		wheelHorizontal(wheelHorizontal),
		wheelRelativity(wheelRelativity),
		wheelSensitivity(wheelSensitivity) {
	}
	
	Slider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		const PSRVec2f& value,
		sf::Vector2i division,
		sf::Vector2f sliderScale,
		Key key,
		bool wheelHorizontal
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(value),
		division(division),
		sliderScale(sliderScale),
		key(key),
		wheelHorizontal(wheelHorizontal),
		wheelRelativity(SliderWheelAction::Relativity::RelationArea),
		wheelSensitivity(1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)) {
	}
	
	Slider* Slider::Make::make(InitInfo initInfo) {
		return new Slider{std::move(*this), initInfo};
	}
	
	Slider::Slider(Make&& make, InitInfo initInfo) :
		BaseSlider(
			std::move(make.slider),
			std::move(make.background),
			makeBoxPtr<SliderInteraction::Make>(
				make.key, make.division, make.wheelHorizontal, make.wheelRelativity, make.wheelSensitivity
			),
			make.value,
			initInfo
		), scale(make.sliderScale) {
	}
	
	Slider::Slider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		const PSRVec2f& value,
		sf::Vector2f sliderScale,
		Key key,
		bool wheelHorizontal,
		SliderWheelAction::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) :
		BaseSlider(
			std::move(slider),
			std::move(background),
			makeBoxPtr<SliderInteraction>(
				key, wheelHorizontal, wheelRelativity, wheelSensitivity
			),
			value
		), scale(sliderScale) {
	}
	
	Slider::Slider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		const PSRVec2f& value,
		sf::Vector2i division,
		sf::Vector2f sliderScale,
		Key key,
		bool wheelHorizontal
	) :
		BaseSlider(
			std::move(slider),
			std::move(background),
			makeBoxPtr<SliderInteraction>(
				key, division, wheelHorizontal
			),
			value
		), scale(sliderScale) {
	}
	
	void Slider::init(InitInfo initInfo) {
		BaseSlider::init(initInfo);
		interactive.init(initInfo, *this);
	}
	
	void Slider::setScale(sf::Vector2f scale) {
		this->scale = scale;
	}
	
	void Slider::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		sliderSize = {size.x * scale.x, size.y * scale.y};
		moveZoneSize = size - sliderSize;
		background->resize(size, position);
		resizeSlider(value->getValue());
	}
	
	sf::Vector2f Slider::getMinSize() const {
		sf::Vector2f minSize{slider->getMinSize()};
		minSize = {minSize.x / scale.x, minSize.y / scale.y};
		return max(minSize, background->getMinSize());
	}
	
	const IUninteractive& Slider::getBackground() const {
		return *background;
	}
	
	const IUninteractive& Slider::getSlider() const {
		return *slider;
	}
	
	Slider* Slider::copy() {
		return new Slider{*this};
	}
	
	bool DecodePointer<Slider>::decodePointer(const YAML::Node& node, Slider*& sliderZone) {
		auto slider{node["slider"].as<BoxPtr<IUninteractive> >()};
		auto background{node["background"].as<BoxPtr<IUninteractive> >()};
		auto value{Buffer::get<SRVec2f>(node["value"])};
		auto sliderScale{convDef(node["slider-scale"], sf::Vector2f{1.0f, 0.5f})};
		auto key{convDef(node["key"], Key::MouseLeft)};
		auto wheelHorizontal{convBoolDef(node["default-wheel"], "horizontal", "vertical", false)};
		
		if(!node["division"]) {
			auto wheelRelativity{convDef(node["wheel-relativity"], SliderWheelAction::Relativity::RelationArea)};
			auto wheelSensitivity{convDef(node["wheel-sensitivity"], sf::Vector2f{0.2f, 0.2f})};
			
			sliderZone = new Slider{std::move(slider), std::move(background), value, sliderScale, key, wheelHorizontal, wheelRelativity, wheelSensitivity};
		} else {
			auto division{node["division"].as<sf::Vector2i>()};
			
			sliderZone = new Slider{std::move(slider), std::move(background), value, division, sliderScale, key, wheelHorizontal};
		}
		return true;
	}
}