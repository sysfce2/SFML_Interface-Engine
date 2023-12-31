#include "TextSelectionAction.hpp"

#include "IE/component/IComponent/Text/Text.hpp"

#include <cmath>

namespace ie {
	TextSelectionAction* TextSelectionAction::Make::make(BasicActionInitInfo<Text&> init_info) {
		return new TextSelectionAction{std::move(*this), init_info};
	}
	
	TextSelectionAction::TextSelectionAction(Make&&, BasicActionInitInfo<Text&> init_info) : text(&init_info.additional), start(), end() {
	}
	
	TextSelectionAction::TextSelectionAction() : text(nullptr), start(), end() {
	}
	
	void TextSelectionAction::init(BasicActionInitInfo<Text&> init_info) {
		text = &init_info.additional;
	}
	
	void TextSelectionAction::start_pressed() {
		text->set_selection_start(start = text->get_character(sf::Vector2f{mouse_position_}));
	}
	
	void TextSelectionAction::stop_pressed() {
	}
	
	void TextSelectionAction::while_pressed() {
		text->set_selection_end(end = text->get_character(sf::Vector2f{mouse_position_}));
		if(start && end) {
			auto local_start = start, local_end = end;
			
			if(start.some() > end.some())
				std::swap(local_start, local_end);
			
			for(auto iterator = local_start.some(); iterator != local_end.some(); ++iterator) {
				(*iterator)->set_selection(true);
				(*iterator)->set_active(true);
			}
		}
	}
	
	void TextSelectionAction::while_not_pressed() {
	}
	
	orl::Option<std::vector<BaseCharacter*>::iterator> TextSelectionAction::get_start() {
		return start;
	}
	
	orl::Option<std::vector<BaseCharacter*>::iterator> TextSelectionAction::get_end() {
		return end;
	}
	
	void TextSelectionAction::update(sf::Vector2i mouse_position, bool press) {
		if(press && start && end) {
			auto local_start = start, local_end = end;
			
			if(start.some() > end.some())
				std::swap(local_start, local_end);
			
			for(auto iterator = local_start.some(); iterator != local_end.some(); ++iterator) {
				(*iterator)->set_selection(false);
			}
		}
		BasicBaseKeyAction<Text&>::update(mouse_position, press);
	}
	
	TextSelectionAction* TextSelectionAction::copy() {
		return new TextSelectionAction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<TextSelectionAction>::decode_pointer(const YAML::Node&, TextSelectionAction*& text_selection_action) {
		text_selection_action = new TextSelectionAction{};
		return true;
	}
	*/
}