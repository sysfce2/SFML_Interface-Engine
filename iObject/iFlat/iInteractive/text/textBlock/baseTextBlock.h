#pragma once
#include "SFML/Graphics.hpp"
#include "../../simple/interactiveSimple.h"
#include "../character/baseCharacter.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include "../character/baseCharacter.h"
#include "../textVariables.h"

namespace ui {
	class BaseTextBlock{
	protected:
        ui::InteractionManager *interactionManager;
        ui::InteractionStack *interactionStack;

        TextVariables textVariables;
	public:
        struct Edge{
            int start, end;
        };
        BaseTextBlock();

        BaseTextBlock(TextVariables textVariables);

        void setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Font *font , uint size);
        virtual void init(ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack);

        virtual bool in(sf::Vector2f mousePosition) = 0;

        virtual std::vector<BaseCharacter*> character() = 0;

        virtual void update() = 0;

        virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;

        virtual BaseTextBlock *copy() = 0;
    };
}
