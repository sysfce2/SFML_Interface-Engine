#include "buttonWithPanel.hpp"

namespace ui {
	ButtonWithPanel::ButtonWithPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background) :
		BaseButton(std::move(background), dynamicCast<IInteraction>(std::move(interaction))), panel(std::move(panel)) {
	}
	
	ButtonWithPanel::ButtonWithPanel(const ButtonWithPanel& other) :
		BaseButton(BoxPtr{other.background}, BoxPtr{other.interaction}), panel(BoxPtr{other.panel}) {
		dynamic_cast<IDisplayPanelInteraction&>(*interaction).setPanel(*panel);
	}
	
	void ButtonWithPanel::init(InteractiveInitInfo interactiveInitInfo) {
		BaseButton::init(interactiveInitInfo);
		panel->init(interactiveInitInfo.toGeneral(*interactionManager, *interactionStack));
		dynamic_cast<IDisplayPanelInteraction&>(*interaction).init({interactiveInitInfo.toGeneral(*interactionManager, *interactionStack), *panel});
	}
	
	void ButtonWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		BaseButton::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f ButtonWithPanel::getMinSize() const {
		sf::Vector2f backgroundMinSize{background->getMinSize()};
		sf::Vector2f panelMinSize{panel->getMinSize()};
		return {std::max(backgroundMinSize.x, panelMinSize.x), std::max(backgroundMinSize.y, panelMinSize.y)};
	}
	
	ButtonWithPanel* ButtonWithPanel::copy() {
		return new ButtonWithPanel{*this};
	}
	
	void ButtonWithPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		BaseButton::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<ButtonWithPanel>::decodePointer(const YAML::Node& node, ButtonWithPanel*& buttonWithPanel) {
		buttonWithPanel = new ButtonWithPanel{
			node["panel"].as<BoxPtr<Panel> >(),
			node["display-interaction"].as<BoxPtr<IDisplayPanelInteraction> >(),
			node["background"].as<BoxPtr<IScalable> >()
		};
		return true;
	}
}
