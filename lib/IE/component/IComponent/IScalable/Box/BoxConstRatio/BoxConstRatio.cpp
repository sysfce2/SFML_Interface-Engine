#include "BoxConstRatio.hpp"

namespace ie {
	BoxConstRatio::Make::Make(
		BoxPtr<IScalable::Make>&& const_object,
		BoxPtr<IScalable::Make>&& second_object,
		BoxPtr<IUninteractive::Make>&& background,
		float aspect_ratio,
		Corner corner,
		sf::Vector2f min_size
	) :
		const_object(std::move(const_object)),
		second_object(std::move(second_object)),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		corner(corner),
		min_size(min_size) {
	}
	
	BoxConstRatio* BoxConstRatio::Make::make(InitInfo init_info) {
		return new BoxConstRatio{std::move(*this), init_info};
	}
	
	BoxConstRatio::BoxConstRatio(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		background_(make.background->make(init_info)),
		const_object_(make.const_object->make(init_info)),
		second_object_(make.second_object->make(init_info.copy(second_draw_manager_))),
		vertical_side_(make.corner == Corner::UpLeft || make.corner == Corner::UpRight),
		horizontal_side_(make.corner == Corner::UpLeft || make.corner == Corner::DownLeft),
		render_second_(true),
		aspect_ratio_(make.aspect_ratio) {
		init_info.draw_manager.add(*this);
	}
	
	BoxConstRatio::BoxConstRatio(
		BoxPtr<IScalable>&& const_object,
		BoxPtr<IScalable>&& second_object,
		BoxPtr<IUninteractive>&& background,
		float aspect_ratio,
		Corner corner,
		sf::Vector2f min_size
	) :
		Box(min_size),
		background_(std::move(background)),
		const_object_(std::move(const_object)),
		second_object_(std::move(second_object)),
		vertical_side_(corner == Corner::UpLeft || corner == Corner::UpRight),
		horizontal_side_(corner == Corner::UpLeft || corner == Corner::DownLeft),
		render_second_(true),
		aspect_ratio_(aspect_ratio) {
	}
	
	BoxConstRatio::BoxConstRatio(const BoxConstRatio& other) :
		Box(other), background_(other.background_), const_object_(other.const_object_), second_object_(other.second_object_),
		vertical_side_(other.vertical_side_), horizontal_side_(other.horizontal_side_), render_second_(other.render_second_), aspect_ratio_(other.aspect_ratio_) {
	}
	
	void BoxConstRatio::init(InitInfo init_info) {
		init_info.draw_manager.add(*this);
		background_->init(init_info);
		const_object_->init(init_info);
		second_object_->init(init_info.copy(second_draw_manager_));
	}
	
	Corner BoxConstRatio::get_corner() {
		if(vertical_side_) {
			if(horizontal_side_) {
				return Corner::UpLeft;
			}
			return Corner::UpRight;
		} else {
			if(horizontal_side_) {
				return Corner::DownLeft;
			}
			return Corner::DownRight;
		}
	}
	
	void BoxConstRatio::draw() {
		if(render_second_) {
			second_draw_manager_.draw();
		}
	}
	
	void BoxConstRatio::set_position(sf::Vector2f position) {
		BoxConstRatio::move(position - layout_.position);
	}
	
	void BoxConstRatio::move(sf::Vector2f position) {
		layout_.move(position);
		background_->move(position);
		const_object_->move(position);
		second_object_->move(position);
	}
	
	void BoxConstRatio::set_size(sf::Vector2f size) {
		resize(size, layout_.position);
	}
	
	void BoxConstRatio::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		sf::Vector2f const_size = sf::Vector2f(size.x / size.y > aspect_ratio_ ? sf::Vector2f{size.y * aspect_ratio_, size.y} : sf::Vector2f{size.x, size.x / aspect_ratio_});
		sf::Vector2f second_size = sf::Vector2f(size.x / size.y > aspect_ratio_ ? sf::Vector2f{size.x - const_size.x, size.y} : sf::Vector2f{size.x, size.y - const_size.y});
		
		sf::Vector2f const_position = sf::Vector2f{0, 0};
		sf::Vector2f second_position = sf::Vector2f{0, 0};
		
		sf::Vector2f second_min_size = second_object_->get_min_size();
		render_second_ = second_size.x > second_min_size.x && second_size.y > second_min_size.y;
		if(render_second_) {
			if(size.x / size.y > aspect_ratio_) {
				if(horizontal_side_) {
					second_position.x = const_size.x;
				} else {
					const_position.x = second_size.x;
				}
			} else {
				if(vertical_side_) {
					second_position.y = const_size.y;
				} else {
					const_position.y = second_size.y;
				}
			}
		} else {
			const_position = (layout_.size - const_size) / 2.0f;
		}
		
		const_position += position;
		second_position += position;
		
		const_object_->resize(const_size, const_position);
		second_object_->resize(second_size, second_position);
		background_->resize(size, position);
	}
	
	bool BoxConstRatio::update_interactions(sf::Vector2f mouse_position) {
		if(render_second_ && second_object_->in_area(mouse_position)) {
			return second_object_->update_interactions(mouse_position);
		}
		if(const_object_->in_area(mouse_position)) {
			return const_object_->update_interactions(mouse_position);
		}
		return background_->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstRatio::get_min_size() const {
		sf::Vector2f const_min_size{const_object_->get_min_size()};
		const_min_size = sf::Vector2f{std::max(const_min_size.x, const_min_size.y * aspect_ratio_), std::max(const_min_size.y, const_min_size.x / aspect_ratio_)};
		return max(const_min_size, background_->get_min_size(), minimum_size_);
	}
	
	sf::Vector2f BoxConstRatio::get_normal_size() const {
		sf::Vector2f const_normal_size{const_object_->get_normal_size()};
		sf::Vector2f second_normal_size{second_object_->get_normal_size()};
		//sf::Vector2f normal_size{std::max(const_normal_size.x, const_normal_size.y * aspect_ratio), std::max(const_normal_size.y, const_normal_size.x / aspect_ratio)};
		sf::Vector2f normal_size{const_normal_size.x + second_normal_size.x, std::max(const_normal_size.y, second_normal_size.y)};
		return max(normal_size, background_->get_normal_size());
	}
	
	IUninteractive& BoxConstRatio::get_background() {
		return *background_;
	}
	
	const IUninteractive& BoxConstRatio::get_background() const {
		return *background_;
	}
	
	IScalable& BoxConstRatio::get_first_object() {
		return *const_object_;
	}
	
	const IScalable& BoxConstRatio::get_first_object() const {
		return *const_object_;
	}
	
	IScalable& BoxConstRatio::get_second_object() {
		return *second_object_;
	}
	
	const IScalable& BoxConstRatio::get_second_object() const {
		return *second_object_;
	}
	
	BoxConstRatio* BoxConstRatio::copy() {
		return new BoxConstRatio{*this};
	}
	
	void BoxConstRatio::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		const_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxConstRatio>::decode_pointer(const YAML::Node& node, BoxConstRatio*& box_with_const_ratio) {
		box_with_const_ratio = new BoxConstRatio{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable> >(),
			BoxPtr{conv_def_ptr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			conv_def(node["corner"], Corner::UpLeft),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;

	}
	*/
}