#include "ClickHidePanelInteraction.hpp"

namespace ie {
	ClickHidePanelInteraction::ClickHidePanelInteraction(Key key, bool onlyOnParent) :
		ClickPanelInteraction(makeBoxPtr<PanelAction, HidePanelAction>(onlyOnParent), key) {
	}
	
	ClickHidePanelInteraction* ClickHidePanelInteraction::copy() {
		return new ClickHidePanelInteraction{*this};
	}
	
	bool DecodePointer<ClickHidePanelInteraction>::decodePointer(const YAML::Node& node, ClickHidePanelInteraction*& clickHidePanelInteraction) {
		clickHidePanelInteraction = new ClickHidePanelInteraction{
			node["key"].as<Key>(),
			convDef(node["only-on-parent"], false)
		};
		return true;
	}
}
