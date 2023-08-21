#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxConstBorder/BoxConstBorder.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxConstBorder) {
	InitInfoData data{{100, 100}};
	
	ui::BoxConstBorder boxConstBorder{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			2,
			ui::Side::left
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxConstBorder.getMinSize(), (sf::Vector2f{2, 0}));
	ASSERT_EQ(boxConstBorder.getNormalSize(), (sf::Vector2f{2, 0}));
	ASSERT_EQ(boxConstBorder.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstBorder.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstBorder.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstBorder.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstBorder.updateInteractions({}), true);
	
	boxConstBorder.setSize({5, 11});
	ASSERT_EQ(boxConstBorder.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxConstBorder.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxConstBorder.setPosition({19, 39});
	ASSERT_EQ(boxConstBorder.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxConstBorder.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxConstBorder.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxConstBorder.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstBorder.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstBorder.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxConstBorder.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxConstBorder.move({10, 5});
	ASSERT_EQ(boxConstBorder.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxConstBorder.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxConstBorder.png"));
}