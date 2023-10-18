#pragma once

#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxBorderHorizontal : public Box, public virtual IScalableObjectsArray {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			std::vector<float> bounds;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f min_size = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f min_size = {});
			
			Make(BoxPtr<IScalable::Make>&& first_object, BoxPtr<IScalable::Make>&& second_object, float bound = 0.5f, sf::Vector2f min_size = {});
			
			BoxBorderHorizontal* make(InitInfo init_info) override;
		};
		
		BoxBorderHorizontal(Make&& make, InitInfo init_info);
		
		BoxBorderHorizontal(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f min_size = {});
		
		BoxBorderHorizontal(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f min_size = {});
		
		BoxBorderHorizontal(BoxPtr<IScalable>&& first_object, BoxPtr<IScalable>&& second_object, float bound = 0.5f, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		std::size_t get_array_size() const override;
		
		IScalable& get_object_at(std::size_t index) override;
		
		const IScalable& get_object_at(std::size_t index) const override;
		
		BoxBorderHorizontal* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects;
		std::vector<float> bounds;
	};
	
	template<>
	struct DecodePointer<BoxBorderHorizontal> {
		static bool decode_pointer(const YAML::Node& node, BoxBorderHorizontal*& box_with_border_horizontal);
	};
}