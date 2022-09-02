#include "dontMovePanelInteraction.hpp"

namespace ui {
	DontMovePanelInteraction::DontMovePanelInteraction() : MovePanelInteraction() {}
	
	void DontMovePanelInteraction::move(sf::Vector2i mousePosition) {}
	
	void DontMovePanelInteraction::start(sf::Vector2i mousePosition) {}
	
	bool DontMovePanelInteraction::update(sf::Vector2i mousePosition) { return false; }
	
	void DontMovePanelInteraction::init(Panel &panel, PanelManager &panelManager) {}
	
	void DontMovePanelInteraction::setPanel(Panel &panel) {}
	
	DontMovePanelInteraction *DontMovePanelInteraction::copy() {
		return new DontMovePanelInteraction{};
	}

    DontMovePanelInteraction *DontMovePanelInteraction::createFromYaml(const YAML::Node &node) {
        return new DontMovePanelInteraction{};
    }
}