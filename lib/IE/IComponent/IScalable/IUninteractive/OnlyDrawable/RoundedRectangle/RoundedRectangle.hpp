#pragma once

#include "../OnlyDrawable.hpp"
#include "../../IUninteractiveLayout/IUninteractiveLayout.hpp"

namespace ie {
	class RoundedRectangle : public OnlyDrawable, public virtual IUninteractiveLayout {
	public:
		struct Make : public virtual IUninteractiveLayout::Make {
			sf::Color color;
			float radius;
			
			Make(sf::Color color, float radius);
			
			RoundedRectangle* make(InitInfo initInfo) override;
		};
		
		RoundedRectangle(Make&& make, InitInfo initInfo);
		
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		RoundedRectangle* copy() override;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		sf::RectangleShape horizontalRectangle;
		sf::RectangleShape verticalRectangle;
		sf::CircleShape circle;
		float radius;
	};
	
	template<>
	struct DecodePointer<RoundedRectangle> {
		static bool decodePointer(const YAML::Node& node, RoundedRectangle*& roundedRectangle);
	};
	
	template<>
	bool determine<RoundedRectangle>(const YAML::Node& node);
}