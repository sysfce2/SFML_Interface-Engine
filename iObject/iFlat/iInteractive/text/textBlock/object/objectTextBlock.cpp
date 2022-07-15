#include "objectTextBlock.h"
#include "../../character/simple/character.h"
ui::ObjectTextBlock::ObjectTextBlock(ui::IObject* object, sf::Vector2f size, bool isCharacter) : objectCharacter(object), object(object), isCharacter(isCharacter) {
    sf::Vector2f minSize{object->getMinSize()};
    object->setSize({std::max(size.x, minSize.x), std::max(size.y, minSize.y)});
}

void ui::ObjectTextBlock::init(sf::RenderTarget &renderTarget, ui::InteractionStack &interactionStack, ui::InteractionManager &interactionManager, ui::PanelManager &panelManager) {
    BaseTextBlock::init(renderTarget, interactionStack, interactionManager, panelManager);
    object->init(renderTarget, interactionStack, interactionManager, panelManager);
}

bool ui::ObjectTextBlock::in(sf::Vector2f mousePosition) {
    return objectCharacter.in(mousePosition);
}

std::vector<ui::BaseCharacter*> ui::ObjectTextBlock::character() {
    std::vector<ui::BaseCharacter*> result;
    if(!isCharacter){
        result.push_back(new Character{L'\n', textVariables});
    }

    result.push_back(&objectCharacter);

    if(!isCharacter){
        result.push_back(new Character{L'\n', textVariables});
    }

    return result;
}

void ui::ObjectTextBlock::update() {
    object->update();
}

bool ui::ObjectTextBlock::updateInteractions(sf::Vector2f mousePosition) {
    return object->updateInteractions(mousePosition);
}

ui::BaseTextBlock *ui::ObjectTextBlock::copy() {
    return new ObjectTextBlock{object, object->getSize(), isCharacter};
}
