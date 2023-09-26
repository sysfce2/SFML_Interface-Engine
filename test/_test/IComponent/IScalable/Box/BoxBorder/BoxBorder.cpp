#include <gtest/gtest.h>
#include <IE/IComponent/IScalable/Box/BoxBorder/BoxBorder.hpp>
#include <IE/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxBorder) {
	InitInfoData data{{100, 100}};
	
	ie::BoxBorder boxBorder{
		{
			ie::makeVector(
				ie::makeVector(
					ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
					ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
				),
				ie::makeVector(
					ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Blue),
					ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Yellow)
				)
			)
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 4);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxBorder.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorder.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorder.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorder.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorder.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBorder.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBorder.updateInteractions({}), true);
	
	boxBorder.setSize({5, 11});
	ASSERT_EQ(boxBorder.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxBorder.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxBorder.setPosition({19, 39});
	ASSERT_EQ(boxBorder.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxBorder.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxBorder.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxBorder.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBorder.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBorder.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxBorder.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxBorder.move({10, 5});
	ASSERT_EQ(boxBorder.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxBorder.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxBorder.png"));
}