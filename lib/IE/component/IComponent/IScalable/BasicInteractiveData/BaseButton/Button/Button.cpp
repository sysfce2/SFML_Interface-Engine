#include "Button.hpp"

namespace ie {
	Button::Make::Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction::Make>&& interaction) :
		background(std::move(background)), interaction(std::move(interaction)) {
	}
	
	Button* Button::Make::make(InitInfo init_info) {
		return new Button{std::move(*this), init_info};
	}
	
	Button::Button(Make&& make, InitInfo init_info) :
		BaseButton(std::move(make.background), init_info), interactive_(std::move(make.interaction), init_info, {}) {
	}
	
	Button::Button(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction) :
		BaseButton(std::move(background)), interactive_(std::move(interaction)) {
	}
	
	void Button::init(InitInfo init_info) {
		interactive_.init(init_info, {});
		BaseButton::init(init_info);
	}
	
	Button* Button::copy() {
		return new Button{*this};
	}
	
	void Button::update() {
		interactive_.update();
	}
	
	bool Button::update_interactions(sf::Vector2f mouse_position) {
		bool result{BaseButton::update_interactions(mouse_position)};
		interactive_.update_interactions();
		return result;
	}
}

orl::Option<ie::Button::Make> ieml::Decode<char, ie::Button::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::Button::Make{
		map.at("background").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("interaction").except().as<ie::BoxPtr<ie::IBaseInteraction::Make> >().move_except(),
	};
}
