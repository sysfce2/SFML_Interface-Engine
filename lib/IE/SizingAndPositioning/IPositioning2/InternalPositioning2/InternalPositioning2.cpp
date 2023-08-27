#include "InternalPositioning2.hpp"

namespace ie {
	InternalPositioning2::Make::Make(sf::Vector2f coefficient) : coefficient(coefficient) {
	}
	
	InternalPositioning2* InternalPositioning2::Make::make(Positioning2InitInfo initInfo) {
		return new InternalPositioning2{std::move(*this), initInfo};
	}
	
	InternalPositioning2::InternalPositioning2(Make&& make, Positioning2InitInfo) :
		vertical(std::max(0.f, std::min(1.f, make.coefficient.y))),
		horizontal(std::max(0.f, std::min(1.f, make.coefficient.x))) {
	}
	
	InternalPositioning2::InternalPositioning2(sf::Vector2f coefficient) :
		vertical(std::max(0.f, std::min(1.f, coefficient.y))), horizontal(std::max(0.f, std::min(1.f, coefficient.x))) {
	}
	
	void InternalPositioning2::init(sf::RenderTarget&) {
	}
	
	sf::Vector2f InternalPositioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		return {
			horizontal.findPosition(parentPosition.x, objectSize.x, parentSize.x, 0),
			vertical.findPosition(parentPosition.y, objectSize.y, parentSize.y, 0)
		};
	}
	
	InternalPositioning2* InternalPositioning2::copy() {
		return new InternalPositioning2{*this};
	}
	
	bool DecodePointer<InternalPositioning2>::decodePointer(const YAML::Node& node, InternalPositioning2*& internalPositioning2) {
		internalPositioning2 = new InternalPositioning2{node["coefficient"].as<sf::Vector2f>()};
		return true;
	}
}