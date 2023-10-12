#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxConstBezel/BoxConstBezel.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxConstBezel) {
	InitInfoData data{{100, 100}};
	
	ie::BoxConstBezel boxConstBezel{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Red),
			1
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxConstBezel.getMinSize(), (sf::Vector2f{2, 2}));
	ASSERT_EQ(boxConstBezel.getNormalSize(), (sf::Vector2f{2, 2}));
	ASSERT_EQ(boxConstBezel.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstBezel.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstBezel.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstBezel.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstBezel.updateInteractions({}), true);
	
	boxConstBezel.setSize({5, 11});
	ASSERT_EQ(boxConstBezel.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxConstBezel.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxConstBezel.setPosition({19, 39});
	ASSERT_EQ(boxConstBezel.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxConstBezel.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxConstBezel.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxConstBezel.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstBezel.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstBezel.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxConstBezel.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxConstBezel.move({10, 5});
	ASSERT_EQ(boxConstBezel.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxConstBezel.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxConstBezel.png"));
}