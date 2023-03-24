#include "../../../../../../../../../createTestProgram/createTestProgram.hpp"

TEST(Sprite, draw) {
    sf::Texture testTexture;
    testTexture.loadFromFile("../test/tests/7-stage-object/ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/sprite/src/gigachad.jpg");

    Program testProgram{
        new ui::Interface{
            new ui::Sprite{
                testTexture
            }
        }
    };

    ASSERT_TRUE(testProgram.renderTexture.getTexture() == testTexture);
}

TEST(Sprite, YAML) {
    Program testProgram{
	    new ui::Interface{
            ui::loadFromYaml<ui::IScalable>("../test/tests/7-stage-object/ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/sprite/src/test.yaml")
        }
    };

	ASSERT_TRUE((testProgram.interface->getMinSize() == sf::Vector2f{5, 5}));
	ASSERT_TRUE((testProgram.interface->getNormalSize() == sf::Vector2f{10, 10}));

    sf::Image testImage;
    testImage.loadFromFile("../test/tests/7-stage-object/ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/sprite/src/gigachad.jpg");

    sf::Image renderImage{testProgram.renderTexture.getTexture().copyToImage()};

    ASSERT_TRUE((renderImage.getSize() == sf::Vector2u{10, 10}));

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            ASSERT_TRUE((renderImage.getPixel(x, y) == testImage.getPixel(x, y)));
        }
    }
}
