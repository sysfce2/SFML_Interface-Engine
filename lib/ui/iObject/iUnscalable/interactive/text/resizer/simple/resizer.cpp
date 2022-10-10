#include "resizer.h"

namespace ui {
    Resizer::Resizer(float lineSpacing, Align align) : BaseResizer{lineSpacing, align}{}

    void Resizer::move(sf::Vector2f position) {
        startRender += position;
        endRender += position;

        for (BaseCharacter*& character : *characters) {
            character->move(position);
        }

        for (BaseLine*& line : *lines) {
            line->move(position);
        }
    }

    void Resizer::setPosition(sf::Vector2f position) {
        sf::Vector2f offset{position - startRender};
        for (BaseCharacter*& character : *characters) {
            character->move({offset});
        }

        for (BaseLine*& line : *lines) {
            line->move(offset);
        }

        endRender += offset;
        startRender = position;
    }

    void Resizer::printCharacter(BaseCharacter *character, float kerning) {
        character->setPosition(nextPosition);
        nextPosition.x += character->getAdvance() + kerning;
        distanceEnter++;
    }

    float Resizer::equalize(uint i) {
        if (i > 0){
            float lineSize = 0;
            for (int j = i - distanceEnter; j < i; ++j) {
                float characterSize = (*characters)[j]->getHeight();
                if (lineSize < characterSize)
                    lineSize = characterSize;
            }
            sf::Vector2f offset{endRender.x - ((*characters)[i - 1]->getPosition().x), lineSize};
/*
            if ((*characters)[i - 1]->isSpecial() != BaseCharacter::Special::space)
                offset.x -= (*characters)[i - 1]->getAdvance();
*/

            switch (align) {
                case Align::left:
                    offset.x = 0;
                    break;
                case Align::center:
                    offset.x /= 2;
                    break;
            }

            for (uint j = i - distanceEnter; j < i; ++j) {
                (*characters)[j]->move(offset);
            }

            std::vector<BaseLine *> *oldLine = nullptr;
            float startLine = 0;
            for (uint j = i - distanceEnter; j < i; ++j) {
                BaseCharacter* character = (*characters)[j];
                std::vector<BaseLine *> &characterLine = character->getLine();
                sf::Vector2f characterPos = character->getPosition();
                if (oldLine != &characterLine) {
                    if (oldLine) {
                        for (BaseLine *&line: *oldLine) {
                            BaseLine *copyLine = line->copy();
                            copyLine->resize(startLine, characterPos.x, characterPos.y);
                            this->lines->push_back(copyLine);
                        }
                    }

                    oldLine = &characterLine;
                    startLine = characterPos.x;
                }
            }

            if (oldLine) {
                BaseCharacter* character = (*characters)[i - ((characters->size() == i || (*characters)[i]->isEnter() || i == 1) ? 1 : 2)];
                sf::Vector2f characterPos = character->getPosition();
                characterPos.x += character->getAdvance();

                for (BaseLine *&line: *oldLine) {
                    BaseLine *copyLine = line->copy();
                    copyLine->resize(startLine, characterPos.x, characterPos.y);
                    this->lines->push_back(copyLine);
                }
            }
            return lineSize;
        }
        return 0;
    }

    void Resizer::porting(int i) {
        float lineSize = equalize(i);
        nextPosition.y += lineSize * lineSpacing;
        nextPosition.x = startRender.x;

        distanceEnter = 0;
    }

    void Resizer::autoPorting(int i) {

        distanceEnter -= distanceSpace;
        porting(i - distanceSpace);

        for (uint j = i - distanceSpace; j < i; ++j) {
            float kerning;
            if (j < i - 1)
                kerning = (*characters)[j]->getKerning((*characters)[j + 1]->getChar());
            printCharacter((*characters)[j], kerning);
        }

        distanceEnter = distanceSpace;
        distanceSpace = 0;
    }
    
    void Resizer::resize(sf::Vector2f size, sf::Vector2f position) {
        if(size.x == endRender.x - startRender.x){
            sf::Vector2f offset{position - startRender};
            for (BaseCharacter*& character : (*characters)) {
                character->move(offset);
            }

            for (BaseLine*& line : *lines) {
                line->move(offset);
            }

            startRender = position;
            endRender = position + size;
            return;
        }

        for (BaseLine*& line : *lines) {
            delete line;
        }
        lines->clear();

        startRender = position;
        endRender = position + size;
        this->nextPosition = startRender;


        for (int i = 0; i < (*characters).size(); i++) {
            BaseCharacter* character = (*characters)[i];

            float kerning = 0;

            BaseCharacter::Special specialText = character->isSpecial();

            switch (specialText) {
                case BaseCharacter::Special::no:
                    printCharacter(character, kerning);
                    distanceSpace++;
                    break;
                case BaseCharacter::Special::space:
                    if (this->nextPosition.x <= endRender.x){
                        printCharacter(character, kerning);
                        distanceSpace = 0;
                    } else{
                        autoPorting(i);
                        printCharacter(character, kerning);
                    }
                    break;
                case BaseCharacter::Special::enter:
                    if (this->nextPosition.x > endRender.x)
                        autoPorting(i);
                    porting(i);
                    break;
            }
        }

        if (endRender.x < this->nextPosition.x){
            autoPorting(characters->size());
        }
        equalize((*characters).size());

        distanceEnter = 0;
        distanceSpace = 0;
    }

    sf::Vector2f Resizer::getMinSize() {

        sf::Vector2f minSize = {0, 0};
        float wordSizeX = 0;

        for (BaseCharacter *character : *characters) {
            if (character->isSpecial() == BaseCharacter::Special::no){
                wordSizeX += character->getAdvance();
            }else{
                if (minSize.x < wordSizeX)
                    minSize.x = wordSizeX;
                wordSizeX = 0;
            }
        }
        if (minSize.x < wordSizeX)
            minSize.x = wordSizeX;

        return minSize;
    }

    sf::Vector2f Resizer::getNormalSize() {
        return getMinSize();
    }

    Resizer *Resizer::copy() {
        return new Resizer(lineSpacing, align);
    }

    bool convertPointer(const YAML::Node &node, Resizer *&resizer) {
        float lineSpacing{1.15};
        BaseResizer::Align align{BaseResizer::Align::left};

        if (node["line-spacing"]) node["line-spacing"] >> lineSpacing;
        if (node["align"]) node["align"] >> align;

        { resizer = new Resizer{lineSpacing, align}; return true; }
    }
}