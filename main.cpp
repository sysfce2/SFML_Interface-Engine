﻿#include <iostream>
#include <array>
#include "lib/ui/UI.h"

template<typename I, I T>
float calculateMediumFPS(std::array<float, T> lastFPS) {
	float sum = 0.0f;
	for(const auto &fps: lastFPS) {
		sum += fps;
	}
	return sum / static_cast<float>(lastFPS.size());
}

int main() {
	ui::yamlBuilderInit();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(400, 200), "IE works!", sf::Style::Default, settings);
	sf::View view(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(window.getSize()));
	window.setFramerateLimit(60);

/*
    sf::Texture textureGigachad;
    textureGigachad.loadFromFile("gigachad.jpg");
	sf::Texture texture;
	texture.loadFromFile("image.png");
	sf::Texture texture_2;
	texture_2.loadFromFile("image_2.png");
    sf::Texture texture_3;
    texture_3.loadFromFile("image_3.png");
	sf::Font font;
	font.loadFromFile("segoeui.ttf");
*/

	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	ui::BasePanel::setFullDebug(true);
	ui::Character::setDebug(true);

	ui::Interface interface {
/*
        new ui::LayerWithBackground{
            new ui::LayerWithMovableBorder{
                new ui::LayerWithBorderHorizontal{
                    {
                        new ui::Empty,
                        new ui::LayerWithMovableBorder{
                            new ui::LayerWithConstRatio{
                                new ui::LayerWithAlternativeObject{
                                    new ui::ButtonWithPanel{
                                        new ui::Panel{
                                            new ui::Text{
                                                {
                                                    new ui::TextBlock{
                                                        U"это ",
                                                        {255, 255, 255, 0},
                                                        &font,
                                                        {},
                                                        {
                                                            new ui::StrikeThrough{{0, 0, 255}}
                                                        }
                                                    },
                                                    new ui::TextBlock{
                                                        U"собственность",
                                                        {255, 255, 255, 0},
                                                        &font,
                                                        {},
                                                        {
                                                            new ui::Underline{{255, 0, 0}},
                                                            new ui::StrikeThrough{{0, 0, 255}},
                                                        }
                                                    },
                                                    new ui::TextBlock{
                                                        U" Артёма",
                                                        {255, 255, 255, 0},
                                                        &font,
                                                        {},
                                                        {
                                                            new ui::Underline{{255, 0, 0}}
                                                        }
                                                    },
                                                    new ui::ObjectTextBlock{
                                                        new ui::Text{
                                                            {
                                                                new ui::TextBlock{
                                                                    U"fack\n",
                                                                    {255, 255, 255, 0},
                                                                    &font,
                                                                    sf::Text::Style::Italic
                                                                },
                                                                new ui::InteractiveTextBlock{
                                                                    0,
                                                                    U"you",
                                                                    {255, 255, 255, 0},
                                                                    &font,
                                                                    sf::Text::Style::Bold
                                                                },
                                                                new ui::ObjectTextBlock{
                                                                    //new ui::ButtonWithPanel{
                                                                    new ui::LayerWithPanel{
                                                                        //new ui::Panel{
                                                                        new ui::ConstPanel{
                                                                            new ui::DebugLayer{
                                                                                new ui::Sprite{texture}
                                                                            },
                                                                            //new ui::PointingHidePanelInteraction,
                                                                            new ui::Sizing2{sf::Vector2f{1, 0.5}, sf::Vector2f{}},
                                                                            new ui::Positioning2{ui::Location2::right, ui::Location2::left},
                                                                        },
                                                                        //new ui::ClickDisplayPanelInteraction{sf::Mouse::BaseButton::left},
                                                                        new ui::Sprite{texture_2}
                                                                    },
                                                                    {50, 50},
                                                                    false
                                                                }
                                                            },
                                                            new ui::FullColor{{255, 0, 0}},
                                                            30,
                                                            &font,
                                                            sf::Color{255, 255, 0},
                                                            sf::Color{200, 200, 200},
                                                            sf::Color{200, 200, 200},
                                                            new ui::Resizer
                                                        },
                                                        {111, 111},
                                                        false
                                                    }
                                                },
                                                new ui::RoundedRectangle{sf::Color(0xffffffff), 10},
                                                14,
                                                &font,
                                                sf::Color{10, 255, 0},
                                                sf::Color{200, 200, 200},
                                                sf::Color{200, 200, 200},
                                                new ui::Resizer
                                            },
                                            new ui::ClickHidePanelInteraction{sf::Mouse::Button::Left},
                                            new ui::Sizing2{sf::Vector2f{1, 0.5}, sf::Vector2f{}},
                                            new ui::Positioning2{ui::Location2::right, ui::Location2::left},
                                        },
                                        new ui::ClickDisplayPanelInteraction{sf::Mouse::Button::Left},
                                        new ui::LayerWithRenderTexture{
                                            new ui::Switch{
                                                new ui::Sprite{texture_2},
                                                new ui::Sprite{texture}
                                            }
                                        }
                                    },
                                    new ui::LayerWithBorderVertical{
                                        new ui::Empty,
                                        new ui::FullColor{sf::Color(0x9f6e5cff)}
                                    },
                                },
                                new ui::Empty,
                                new ui::Empty,
                                1,
                                ui::Corner::downLeft
                            },
                            new ui::Text{
                                {
                                    new ui::TextBlock{
                                        U"Box2D is a 2D rigid body simulation library for games. Programmers can use it in their games to make objects moveSlider in realistic ways and make the game world more interactive. From the game engine's point of view, a physics engine is just a system for procedural animation. \nBox2D is written in portable C++. Most of the types defined in the engine begin with the b2 prefix. Hopefully this is sufficient to avoid name clashing with your game engine."
                                    }
                                },
                                new ui::FullColor{sf::Color(0x9f6e5cff)},
                                14,
                                &font,
                                sf::Color{10, 10, 0},
                                sf::Color{200, 200, 200},
                                sf::Color{200, 200, 200},
                                new ui::Resizer
                            },
                            false
                        },
                        new ui::Empty
                    },
                    std::vector<float>{
                        0.4,
                        0.6
                    }
                },
                new ui::LayerWithConstCenter{
                    new ui::LayerWithAlternativeObject{
                        new ui::LayerWithBorderHorizontal{
                            new ui::LayerWithAlternativeObject{
                                new ui::Sprite{texture_3},
                                new ui::Capsule{sf::Color(0x9f6e5cff)}
                            },
                            new ui::LayerWithAlternativeObject{
                                new ui::Sprite{texture_3},
                                new ui::Capsule{sf::Color(0x9f6e5cff)}
                            }
                        },
                        new ui::LayerWithBorderVertical{
                            {
                                new ui::LayerWithBorderHorizontal{
                                    {
                                        new ui::Empty,
                                        new ui::FullColor{sf::Color(0x9f6e5cff)},
                                        new ui::Empty
                                    },
                                    std::vector<float>{
                                        0.25,
                                        0.75
                                    }
                                },
                                new ui::Empty
                            }
                        }
                    },
                    new ui::Empty,
                    2
                },
                false,
                0.75
            },
            new ui::Sprite{textureGigachad},
            {100.f, 100.f}
        }
*/
		ui::loadFromYaml<ui::IScalable>("../test.yaml"),
		new ui::InteractionStack {
			std::vector<ui::IInteraction *> {
				ui::MouseLambdaInteraction::debug.copy()
			}
		}
	};

	interface.init(window);
    window.setSize(sf::Vector2u(ui::max(interface.getNormalSize(), {1, 1})));
    interface.setSize(ui::max(interface.getNormalSize(), {1, 1}));

	sf::Clock clock;
	std::array<float, 500> lastFPS{};
	
	while(window.isOpen()) {

        lastFPS[0] = 1.f / clock.restart().asSeconds();
		std::rotate(lastFPS.begin(), lastFPS.begin() + 1, lastFPS.end());
		float mediumFPS = calculateMediumFPS(lastFPS);
        window.setTitle(std::to_string(static_cast<int>(mediumFPS)));
		clock.restart();
		
		sf::Event event{};
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
			if(event.type == sf::Event::Resized) {
				sf::Vector2f minSize = interface.getMinSize();
				sf::Vector2f windowSize{static_cast<float>(event.size.width), static_cast<float>(event.size.height)};
				if(windowSize.x < minSize.x || windowSize.y < minSize.y) {
					windowSize = ui::max(windowSize, minSize);
					window.setSize(static_cast<sf::Vector2u>(windowSize));
				}
				view.reset({{}, windowSize});
				window.setView(view);
				interface.setSize(windowSize);
			}
			if(event.type == sf::Event::MouseWheelMoved) {
				sf::Wheel::value = event.mouseWheel.delta;
			}
		}
        interface.setSize(sf::Vector2f{window.getSize()});
		window.clear();
		interface.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), window.getSystemHandle());
		interface.draw();
		interface.drawDebug(window, 0, 2, 90, 90);
		window.display();
	}
}
