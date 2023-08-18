#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/interactive/simple/slider/const/constSlider.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, ConstSlider) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::SRVec2f>(sf::Vector2f{0.f, 0.f});
	ui::ConstSlider constSlider{
		{
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Red),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &constSlider);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(constSlider.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(constSlider.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(constSlider.getSize(), sf::Vector2f{});
	ASSERT_EQ(constSlider.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(constSlider.getPosition(), sf::Vector2f{});
	ASSERT_EQ(constSlider.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(constSlider.updateInteractions({}), true);
	
	constSlider.setSize({5, 11});
	ASSERT_EQ(constSlider.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(constSlider.getAreaSize(), (sf::Vector2f{5, 11}));
	
	constSlider.setPosition({19, 39});
	ASSERT_EQ(constSlider.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(constSlider.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	constSlider.resize({7, 13}, {23, 41});
	ASSERT_EQ(constSlider.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(constSlider.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(constSlider.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(constSlider.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	constSlider.move({10, 5});
	ASSERT_EQ(constSlider.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(constSlider.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/ConstSlider-0.0.png"));
	
	value->setValue(sf::Vector2f{0.0f, 0.7f});
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/ConstSlider-0.7.png"));
	
	value->setValue(sf::Vector2f{0.0f, 1.0f});
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/ConstSlider-1.0.png"));
}