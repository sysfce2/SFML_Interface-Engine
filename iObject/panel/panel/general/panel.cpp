#include "panel.h"
#include "../interaction/hide/hidePanelInteraction.h"

ui::Panel::Panel(IFlat *object, HidePanelInteraction *interaction, Sizing2* sizing, Positioning2* positioning, bool displayed) :
	BasePanel(object, sizing, positioning, displayed), interaction(interaction), interactionManager(nullptr) {}

void ui::Panel::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	BasePanel::init(renderTarget, interactionStack, interactionManager, panelManager);
	initObject(object, renderTarget, interactionStack, interactionManager, this->panelManager);
	this->interactionManager = &interactionManager;
	interaction->init(*this, panelManager);
}

ui::Panel::~Panel() {
	delete interaction;
}

bool ui::Panel::isIndependent() { return true; }

bool ui::Panel::isFree() {
	return panelManager.isFree();
}

void ui::Panel::draw() {
	panelManager.draw();
	BasePanel::draw();
}

void ui::Panel::update() {
	panelManager.update();
	if(oldDisplayed != displayed) {
		if(displayed) {
			interactionManager->addInteraction(*interaction);
		} else {
			interactionManager->deleteInteraction(*interaction);
		}
	}
	BasePanel::update();
}

bool ui::Panel::updateInteractions(sf::Vector2f mousePosition) {
	displayed = true;
	if(panelManager.updateInteractions(mousePosition)) return true;
	return inPanel(mousePosition) && object->updateInteractions(mousePosition);
}

void ui::Panel::copy(ui::Panel *panel) {
	BasePanel::copy(panel);
	panel->interactionManager = this->interactionManager;
}

ui::Panel *ui::Panel::copy() {
	Panel* panel {new Panel(object->copy(), interaction->copy(), sizing->copy(), positioning->copy(), displayed)};
	panel->interaction->setPanel(*panel);
	Panel::copy(panel);
	return panel;
}
