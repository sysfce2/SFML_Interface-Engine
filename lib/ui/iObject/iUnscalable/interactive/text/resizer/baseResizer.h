#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../character/baseCharacter.h"
#include "../line/baseLine.h"

namespace ui {
    class BaseResizer {
    public:
        enum class Align{
            left,
            right,
            center
        };
    protected:
        std::vector<BaseCharacter*>* characters;
        std::vector<BaseLine*>* lines;

        float lineSpacing;
        Align align;
    public:
        BaseResizer(float lineSpacing = 1.15, Align align = Align::left);

        void init(std::vector<BaseCharacter*>& characters, std::vector<BaseLine* >& lines);

        virtual void move(sf::Vector2f position) = 0;

        virtual void setPosition(sf::Vector2f position) = 0;

        virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;

        virtual sf::Vector2f getMinSize() = 0;

        virtual sf::Vector2f getNormalSize() = 0;

        virtual BaseResizer * copy() = 0;

        virtual ~BaseResizer() = default;
    };
}