#pragma once

#include <SFML/System/Vector2.hpp>
#include "ui/interaction/iInteraction/iInteraction.hpp"

namespace ui {
	class Window;
	
	class IWindowResizer {
	public:
		virtual void setWindow(Window* window);
	
		virtual bool update(sf::Vector2i mousePosition) = 0;
	
		virtual ~IWindowResizer() = default;
		
	protected:
		Window* window;
	};
}