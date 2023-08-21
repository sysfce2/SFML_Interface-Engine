#pragma once

#include "../../Enums/Location2/Location2.hpp"
#include "../IPositioning/IPositioning.hpp"
#include "../IPositioning/InternalPositioning/InternalPositioning.hpp"
#include "../IPositioning/InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../IPositioning/MatchPositioning/MatchPositioning.hpp"
#include "../IPositioning/MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../IPositioning/MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "../IPositioning/LambdaPositioning/LambdaPositioning.hpp"

namespace ui {
	class IPositioning2 {
	public:
		virtual ~IPositioning2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget) = 0;
		
		virtual sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual IPositioning2* copy() = 0;
	};
}