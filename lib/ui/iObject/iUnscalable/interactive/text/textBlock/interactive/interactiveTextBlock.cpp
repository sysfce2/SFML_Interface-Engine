#include "interactiveTextBlock.h"
#include "../../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

ui::InteractiveTextBlock::InteractiveTextBlock(ui::IInteraction *interaction, std::u32string  text, sf::Color textColor, sf::Font *font, sf::Text::Style style, std::vector<BaseLine*> lines, int size, sf::Color textSelectionColor,
                                               sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor,sf::Color inactiveBackgroundSelectionColor) :
    interaction(interaction), TextBlock(text, textColor, font, style, lines, size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor), interact(false), oldInteract(false), indexInteraction(-1) {}

ui::InteractiveTextBlock::InteractiveTextBlock(int indexInteraction, std::u32string  text, sf::Color textColor, sf::Font *font, sf::Text::Style style, std::vector<BaseLine*> lines, int size, sf::Color textSelectionColor,
                                               sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor,sf::Color inactiveBackgroundSelectionColor) :
    indexInteraction(indexInteraction), interaction(nullptr), TextBlock(text, textColor, font, style, lines, size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor), interact(false), oldInteract(false) {}

void ui::InteractiveTextBlock::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
	TextBlock::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
    this->interactionManager = &interactionManager;
    if (!interaction)
        interaction = interactionStack.at(indexInteraction);
}

void ui::InteractiveTextBlock::update() {
    if(interact != oldInteract) {
        oldInteract = interact;
        if(interact) {
            interactionManager->addInteraction(*interaction);
        } else {
            interactionManager->deleteInteraction(*interaction);
        }
    }
    interact = false;
}

bool ui::InteractiveTextBlock::updateInteractions(sf::Vector2f mousePosition) {
    interact = true;
    return true;
}

std::vector<ui::BaseCharacter *> ui::InteractiveTextBlock::getCharacters() {
    for (char32_t character : str) {
        textCharacters.push_back(new ui::Character(character, textVariables, lines));
    }
    return textCharacters;
}

bool ui::InteractiveTextBlock::in(sf::Vector2f mousePosition) {
    for (ui::BaseCharacter *character : textCharacters) {
        if (character->in(mousePosition)){
            return true;
        }
    }
    return false;
}

ui::InteractiveTextBlock::InteractiveTextBlock(std::u32string  str, TextVariables textVariables, ui::IInteraction *interaction) :
    TextBlock(str, textVariables, {}), interaction(interaction), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock::InteractiveTextBlock(std::u32string  str, TextVariables textVariables, int indexInteraction) :
    TextBlock(str, textVariables, {}), indexInteraction(indexInteraction), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock *ui::InteractiveTextBlock::copy() {
    if (indexInteraction == -1)
        return new InteractiveTextBlock(str, textVariables, interaction->copy());
    else
        return new InteractiveTextBlock(str, textVariables, indexInteraction);
}

ui::InteractiveTextBlock::~InteractiveTextBlock() {
    if (interaction != nullptr)
        delete interaction;
}

ui::InteractiveTextBlock *ui::InteractiveTextBlock::createFromYaml(const YAML::Node &node) {
    std::u32string  text;
    sf::Color textColor = nullColor;
    sf::Font *font = nullptr;
    sf::Text::Style style = {};
    std::vector<BaseLine*> lines = {};
    int size = 0;
    sf::Color textSelectionColor = nullColor;
    sf::Color backgroundSelectionColor = nullColor;
    sf::Color inactiveTextSelectionColor = nullColor;
    sf::Color inactiveBackgroundSelectionColor = nullColor;

    node["text"] >> text;
    if (node["text-color"]) node["text-color"] >> textColor;
    if (node["text-color"]) node["text-color"] >> textColor;
    if (node["font"]) node["font"] >> font;
    if (node["style"]) node["style"] >> style;
    if (node["size"]) node["size"] >> size;
    if (node["text-selection-color"]) node["text-selection-color"] >> textSelectionColor;
    if (node["background-selection-color"]) node["background-selection-color"] >> backgroundSelectionColor;
    if (node["inactive-text-selection-color"]) node["inactive-text-selection-color"] >> inactiveTextSelectionColor;
    if (node["inactive-background-selection-color"]) node["inactive-background-selection-color"] >> inactiveBackgroundSelectionColor;

    if (node["line"]){
        BaseLine* line;
        node["line"] >> line;
        lines.push_back(line);
    }
    else if (node["lines"]){
        for (const YAML::Node& nodeLine : node["lines"]) {
            BaseLine* line;
            nodeLine >> line;
            lines.push_back(line);
        }
    }

    if (node["interaction"].IsScalar()){
        ui::IInteraction *indexInteraction;
        node["interaction"] >> indexInteraction;
        return new InteractiveTextBlock{indexInteraction, text, textColor, font, style, lines, size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor};
    } else{
        int indexInteraction;
        node["interaction"] >> indexInteraction;
        return new InteractiveTextBlock{indexInteraction, text, textColor, font, style, lines, size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor};
    }

}

