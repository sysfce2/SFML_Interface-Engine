#pragma once

#include "../IPositioning2.hpp"

namespace ui {
	class Positioning2 : public IPositioning2 {
	protected:
		void copy(Positioning2* positioning2);
	
	public:
		Positioning2(BoxPtr<IPositioning>&& horizontal, BoxPtr<IPositioning>&& vertical);
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f offset = {}, bool relativeTarget = false);
		
		Positioning2(Location2 parentLocation, Location2 objectLocation, sf::Vector2f offset = {});
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f objectCoefficient, sf::Vector2f offset, bool relativeTarget = false);
		
		void init(sf::RenderTarget& renderTarget) override;
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) override;
		
		Positioning2* copy() override;
	
	protected:
		BoxPtr<IPositioning> horizontal;
		BoxPtr<IPositioning> vertical;
		sf::RenderTarget* renderTarget;
	};
	
	template<>
	struct DecodePointer<Positioning2> {
		static bool decodePointer(const YAML::Node& node, Positioning2*& positioning2);
	};
}