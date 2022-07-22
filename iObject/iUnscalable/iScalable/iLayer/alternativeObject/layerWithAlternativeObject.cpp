#include "layerWithAlternativeObject.h"
#include <algorithm>

ui::LayerWithAlternativeObject::LayerWithAlternativeObject(ui::IScalable *topObject, ui::IScalable *bottomObject, sf::Vector2f minimumSize) :
	ILayer(minimumSize), LayoutWithTwoObjects(topObject, bottomObject) {}

bool ui::LayerWithAlternativeObject::updateInteractions(sf::Vector2f mousePosition) {
	return firstObject->updateInteractions(mousePosition) || secondObject->updateInteractions(mousePosition);
}

void ui::LayerWithAlternativeObject::resize(sf::Vector2f size, sf::Vector2f position) {
	ILayer::resize(size, position);
	firstObject->resize(size, position);
	secondObject->resize(size, position);
}

ui::LayerWithAlternativeObject *ui::LayerWithAlternativeObject::copy() {
	LayerWithAlternativeObject* layerWithAlternativeObject{new LayerWithAlternativeObject{firstObject->copy(), secondObject->copy(), minimumSize}};
	ILayer::copy(layerWithAlternativeObject);
	return layerWithAlternativeObject;
}
