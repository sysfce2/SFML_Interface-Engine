#include "../../../Enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename T>
	void IBasicMouseInteraction<T>::update(sf::Vector2i mousePosition) {
		getLeftButtonEvent().update(mousePosition, KeyHandler::isKeyPressed(Key::mouseLeft));
		getRightButtonEvent().update(mousePosition, KeyHandler::isKeyPressed(Key::mouseRight));
	}
}
