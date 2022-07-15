#include "baseCharacter.h"
#include "../textBlock/baseTextBlock.h"

ui::BaseCharacter::BaseCharacter() : renderTarget(nullptr) {}

void ui::BaseCharacter::init(sf::RenderTarget &renderTarget) {
    this->renderTarget = &renderTarget;
}

void ui::BaseCharacter::setPosition(const sf::Vector2f position) {
    BaseCharacter::position = position;
}

bool ui::BaseCharacter::in(sf::Vector2f mousePosition) {
    return position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
           position.y < mousePosition.y && position.y + getHeight()> mousePosition.y;
}

const sf::Vector2f &ui::BaseCharacter::getPosition() const {
    return position;
}

void ui::BaseCharacter::move(sf::Vector2f position) {
    this->position += position;
}
