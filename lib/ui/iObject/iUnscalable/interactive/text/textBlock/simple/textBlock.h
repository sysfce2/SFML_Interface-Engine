#pragma once
#include "../baseTextBlock.h"

#include "../../character/simple/character.h"

namespace ui {
	class TextBlock : public BaseTextBlock {
    protected:
        std::u32string  str;

        std::vector<BaseCharacter*> textCharacters;
        std::vector<BaseLine*> lines;

	public:
        TextBlock(std::u32string  str, TextVariables textVariables, std::vector<BaseLine*> lines);

        TextBlock(std::u32string  text, sf::Color textColor = nullColor,
                  sf::Font *font = nullptr, sf::Text::Style style = {}, std::vector<BaseLine*> lines = {}, int size = 0,
                  sf::Color textSelectionColor = nullColor,
                  sf::Color backgroundSelectionColor = nullColor);
        std::vector<BaseCharacter*> getCharacters() override;

        bool in(sf::Vector2f mousePosition);

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        TextBlock * copy() override;

        static TextBlock* createFromYaml(const YAML::Node &node);

        ~TextBlock() override;
	};
}