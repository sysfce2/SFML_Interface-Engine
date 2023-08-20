#include "whileChangingObjectsEvent.hpp"

namespace ui {
	void WhileChangingObjectsEvent::startPressed() {
	}
	
	void WhileChangingObjectsEvent::stopPressed() {
		int indexValue = index->getValue();
		indexValue += offset;
		indexValue = (((indexValue % objectsSize) + objectsSize) % objectsSize);
		index->setValue(indexValue);
	}
	
	void WhileChangingObjectsEvent::whilePressed() {
	}
	
	void WhileChangingObjectsEvent::whileNotPressed() {
	}
	
	WhileChangingObjectsEvent::WhileChangingObjectsEvent(BoxWithChangeableObjects* objects, int offset) :
		ChangeableObjectsEvent(objects), objectsSize(objects->getArraySize()), index(object->getValue()), offset(offset) {
	}
	
	WhileChangingObjectsEvent* WhileChangingObjectsEvent::copy() {
		return new WhileChangingObjectsEvent{*this};
	}
	
	bool DecodePointer<WhileChangingObjectsEvent>::decodePointer(const YAML::Node& node, WhileChangingObjectsEvent*& whileChangingObjectsEvent) {
		whileChangingObjectsEvent = new WhileChangingObjectsEvent{
			convDef<BoxWithChangeableObjects*>(node["object"], nullptr)
		};
		return true;
	}
}