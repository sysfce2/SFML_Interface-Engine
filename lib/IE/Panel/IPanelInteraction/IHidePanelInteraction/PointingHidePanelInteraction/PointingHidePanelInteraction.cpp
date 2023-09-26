
#include "PointingHidePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	PointingHidePanelInteraction::Make::Make(bool onlyOnParent) :
		onlyOnParent(onlyOnParent) {
	}
	
	PointingHidePanelInteraction* PointingHidePanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new PointingHidePanelInteraction{std::move(*this), initInfo};
	}
	
	PointingHidePanelInteraction::PointingHidePanelInteraction(Make&& make, PanelActionInitInfo initInfo) :
		BasePanelInteraction(initInfo), onlyOnParent(make.onlyOnParent) {
	}
	
	PointingHidePanelInteraction::PointingHidePanelInteraction(bool onlyOnParent) : onlyOnParent(onlyOnParent) {
	}
	
	void PointingHidePanelInteraction::start(sf::Vector2i) {
	}
	
	void PointingHidePanelInteraction::update(sf::Vector2i mousePosition) {
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		if(!panel->getParentProcessed() && (onlyOnParent || (!panel->inPanel(pointPosition) && panel->isFree() && !panel->inConstPanels(pointPosition)))) {
			panelManager->hidePanel(panel);
		}
	}
	
	void PointingHidePanelInteraction::finish(sf::Vector2i) {
	}
	
	PointingHidePanelInteraction* PointingHidePanelInteraction::copy() {
		return new PointingHidePanelInteraction{*this};
	}
	
	bool DecodePointer<PointingHidePanelInteraction>::decodePointer(const YAML::Node& node, PointingHidePanelInteraction*& pointingHidePanelInteraction) {
		bool onlyOnParent{false};
		
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		pointingHidePanelInteraction = new PointingHidePanelInteraction{onlyOnParent};
		return true;
	}
}