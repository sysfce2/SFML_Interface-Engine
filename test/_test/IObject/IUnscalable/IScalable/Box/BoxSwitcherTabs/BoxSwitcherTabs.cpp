#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/switcherTabs/boxSwitcherTabs.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxSwitcherTabs) {
	InitInfoData data{{100, 100}};
	
	ui::BoxSwitcherTabs boxSwitcherTabs{
		{
			ui::makeVector(
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red)
			),
			std::make_shared<ui::Sint>(0)
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &boxSwitcherTabs);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxSwitcherTabs.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcherTabs.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcherTabs.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcherTabs.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcherTabs.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcherTabs.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcherTabs.updateInteractions({}), true);
	
	boxSwitcherTabs.setSize({5, 11});
	ASSERT_EQ(boxSwitcherTabs.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxSwitcherTabs.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxSwitcherTabs.setPosition({19, 39});
	ASSERT_EQ(boxSwitcherTabs.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxSwitcherTabs.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxSwitcherTabs.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxSwitcherTabs.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitcherTabs.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitcherTabs.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxSwitcherTabs.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxSwitcherTabs.move({10, 5});
	ASSERT_EQ(boxSwitcherTabs.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxSwitcherTabs.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitcherTabs.png"));
}