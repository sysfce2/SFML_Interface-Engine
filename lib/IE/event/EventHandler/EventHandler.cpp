#include "EventHandler.hpp"

namespace ie {
	auto EventHandler::key_handler() -> KeyHandler& {
		return key_handler_;
	}
	
	auto EventHandler::key_handler() const -> KeyHandler const& {
		return key_handler_;
	}
	
	auto EventHandler::get_key(Key key) -> bool {
		return key_handler_.is_key_pressed(key);
	}
	
	auto EventHandler::set_key(Key key, bool value) -> void {
		if(value) {
			key_handler_.add_key(key);
		} else {
			key_handler_.delete_key(key);
		}
	}
	
	auto EventHandler::get_scroll() -> sf::Vector2f {
		return {scroll_[0], scroll_[1]};
	}
	
	auto EventHandler::set_scroll(size_t id, float value) -> void {
		scroll_[id] = value;
	}
	
	auto EventHandler::get_touch(size_t id) -> orl::Option<sf::Vector2i> {
		if(auto iter{touch_.find(id)}; iter != touch_.end()) {
			return {iter->second};
		}
		return {};
	}
	
	auto EventHandler::set_touch(size_t id, sf::Vector2i value) -> void {
		touch_[id] = value;
	}
	
	auto EventHandler::remove_touch(size_t id) -> void {
		touch_.erase(id);
	}
	
	auto EventHandler::get_joystick_button(size_t id, size_t button_id) -> bool {
		return joystick_buttons_[id][button_id];
	}
	
	auto EventHandler::set_joystick_button(size_t id, size_t button_id, bool value) -> void {
		joystick_buttons_[id][button_id] = value;
	}
	
	auto EventHandler::update() -> void {
		for(auto& item: scroll_) {
			item = 0.f;
		}
	}
	
	auto EventHandler::poll_events(std::vector<Event>& events) -> void {
		for(auto i{size_t{0}}; i < scroll_.size(); ++i) {
			if(scroll_[i] )
			events.emplace_back(Event::Scroll(i, scroll_[i]));
		}
		for(auto [id, position]: touch_) {
			events.emplace_back(Event::Touch(id, position));
		}
		for(auto& [id, joystick]: joystick_buttons_) {
			for(auto [button_id, joystick_button]: joystick) {
				if(joystick_button) {
					events.emplace_back(Event::JoystickButton(id, button_id));
				}
			}
		}
	}
}
