#include "BoxScroll.hpp"

namespace ie {
	BoxScroll::Make::Make(BoxPtr<IComponent::Make>&& object, PSRVec2f normal_object_position, sf::Vector2f min_size) :
		object(std::move(object)), normal_object_position(std::move(normal_object_position)), min_size(min_size) {
	}
	
	BoxScroll* BoxScroll::Make::make(InitInfo init_info) {
		return new BoxScroll{std::move(*this), init_info};
	}
	
	BoxScroll::BoxScroll(Make&& make, InitInfo init_info) :
		BoxWithView(make.min_size, init_info), object(make.object->make(init_info.copy(this->draw_manager))), normal_object_position(make.normal_object_position) {
		normal_object_position->add_setter([&](sf::Vector2f value) {
			this->object->set_position(get_new_object_position(value));
		});
		set_range_bounds(normal_object_position, {0, 0}, {1, 1});
	}
	
	BoxScroll::BoxScroll(BoxPtr<IComponent>&& object, const PSRVec2f& normal_object_position, const sf::Vector2f& min_size) :
		BoxWithView(min_size), object(std::move(object)), normal_object_position(normal_object_position) {
		normal_object_position->add_setter([&](sf::Vector2f vec) {
			this->object->set_position(get_new_object_position(vec));
		});
		set_range_bounds(normal_object_position, {0, 0}, {1, 1});
	}
	
	void BoxScroll::init(InitInfo init_info) {
		BoxWithView::init(init_info);
		object->init(init_info.copy(this->draw_manager));
	}
	
	sf::Vector2f BoxScroll::get_min_size() const {
		return max(minimum_size, object->get_min_size());
	}
	
	sf::Vector2f BoxScroll::get_normal_size() const {
		return object->get_normal_size();
	}
	
	sf::Vector2f BoxScroll::get_new_object_position(sf::Vector2f normal_object_position) {
		sf::Vector2f max_offset{object->get_size() - layout_.size};
		sf::Vector2f offset{max_offset * normal_object_position};
		return layout_.position - offset;
	}
	
	void BoxScroll::resize(sf::Vector2f size, sf::Vector2f position) {
		BoxWithView::resize(size, position);
		
		object->set_size(size);
		
		sf::Vector2f object_size{object->get_size()};
		if(object_size.x == size.x && object_size.y == size.y)
			return object->set_position(position);
		object->set_position(get_new_object_position(normal_object_position->get_value()));
	}
	
	bool BoxScroll::update_interactions(sf::Vector2f mouse_position) {
		return object->update_interactions(mouse_position);
	}
	
	BoxScroll* BoxScroll::copy() {
		return new BoxScroll{*this};
	}
	
	bool DecodePointer<BoxScroll>::decode_pointer(const YAML::Node& node, BoxScroll*& box_scroll) {
		box_scroll = new BoxScroll{
			node["object"].as<BoxPtr<IComponent> >(),
			Buffer::get<SRVec2f>(node["normal-object-position"]),
			(node["min-size"] ? node["min-size"].as<sf::Vector2f>() : sf::Vector2f{0, 0})
		};
		return true;
	}
}