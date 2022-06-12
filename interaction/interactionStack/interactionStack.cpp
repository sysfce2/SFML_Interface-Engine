#include "interactionStack.h"

ui::InteractionStack::InteractionStack(std::vector<ui::IInteraction *> &&interactionStack) : interactionStack(std::move(interactionStack)){}

ui::IInteraction *ui::InteractionStack::at(unsigned index) {
	return interactionStack[index];
}

void ui::InteractionStack::add(ui::IInteraction *element) {
	interactionStack.push_back(element);
}
