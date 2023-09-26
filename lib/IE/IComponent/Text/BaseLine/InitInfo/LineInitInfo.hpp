#pragma once

#include <SFML/Graphics.hpp>

namespace ie {
	using uint = unsigned;
	
	struct LineInitInfo {
		uint size;
		sf::Font& font;
		sf::Color color;
		sf::RenderTarget& renderTarget;
		
		LineInitInfo(uint size, sf::Font& font, const sf::Color& color, sf::RenderTarget& renderTarget);
	};
}