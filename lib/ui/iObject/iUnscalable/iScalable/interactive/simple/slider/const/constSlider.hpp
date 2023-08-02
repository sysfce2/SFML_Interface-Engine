#pragma once

#include "../baseSlider.hpp"

namespace ui {
	class ConstSlider : public BaseSlider {
	public:
		ConstSlider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			const PSRVec2f& value,
			float sliderScale = 1.0f,
			Key key = Key::mouseLeft,
			bool wheelHorizontal = false,
			SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea,
			sf::Vector2f wheelSensitivity = {0.2f, 0.2f}
		);
		
		ConstSlider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			const PSRVec2f& value,
			sf::Vector2i division,
			float sliderScale = 1.0f,
			Key key = Key::mouseLeft,
			bool wheelHorizontal = false
		);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ConstSlider* copy() override;
	
	protected:
		float aspectRatio;
		float sliderScale;
	};
	
	template<>
	struct DecodePointer<ConstSlider> {
		static bool decodePointer(const YAML::Node& node, ConstSlider*& constSlider);
	};
}
