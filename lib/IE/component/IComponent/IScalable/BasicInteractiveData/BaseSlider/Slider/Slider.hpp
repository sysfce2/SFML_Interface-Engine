#pragma once

#include "../BaseSlider.hpp"

namespace ie {
	class Slider : public BaseSlider {
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<INonInteractive::Make> slider;
			BoxPtr<INonInteractive::Make> background;
			MakeDyn<SRVec2F> value;
			sf::Vector2i division;
			sf::Vector2f slider_scale;
			Key key;
			bool wheel_horizontal;
			SliderWheelAction::Relativity wheel_relativity;
			sf::Vector2f wheel_sensitivity;
			
			Make(
				BoxPtr<INonInteractive::Make>&& slider,
				BoxPtr<INonInteractive::Make>&& background,
				MakeDyn<SRVec2F> value,
				sf::Vector2f slider_scale = {1.0f, 0.5f},
				Key key = Key::MouseLeft,
				bool wheel_horizontal = false,
				SliderWheelAction::Relativity wheel_relativity = SliderWheelAction::Relativity::RelationArea,
				sf::Vector2f wheel_sensitivity = {0.2f, 0.2f}
			);
			
			Make(
				BoxPtr<INonInteractive::Make>&& slider,
				BoxPtr<INonInteractive::Make>&& background,
				MakeDyn<SRVec2F> value,
				sf::Vector2i division,
				sf::Vector2f slider_scale = {1.0f, 0.5f},
				Key key = Key::MouseLeft,
				bool wheel_horizontal = false
			);
			
			Slider* make(InitInfo init_info) override;
		};
		
		Slider(Make&& make, InitInfo init_info);
		
		void set_scale(sf::Vector2f scale);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		const INonInteractive& get_background() const;
		
		const INonInteractive& get_slider() const;
		
	protected:
		sf::Vector2f scale_;
	};
}

template<>
struct ieml::Decode<char, ie::Slider::Make> {
	static orl::Option<ie::Slider::Make> decode(ieml::Node const& node);
};
