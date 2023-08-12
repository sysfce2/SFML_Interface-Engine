#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/caption/caption.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <fstream>

TEST(IObject, Caption) {
	InitInfoData data{{100, 100}};
	
	std::basic_ifstream<char32_t> file{"test-src/Caption.txt"};
	std::u32string str;
	std::getline(file, str, U'\0');
	
	sf::Font font{};
	font.loadFromFile("../../example-resources/msyh.ttc");
	ui::Caption caption{
		{
			sf::String{ui::u32stringToUint32String(str)},
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Green),
			font
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &caption);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&caption.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(caption.getMinSize(), (sf::Vector2f{6, 10}));
	ASSERT_EQ(caption.getNormalSize(), (sf::Vector2f{51, 11}));
	ASSERT_EQ(caption.getSize(), sf::Vector2f{});
	ASSERT_EQ(caption.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(caption.getPosition(), sf::Vector2f{});
	ASSERT_EQ(caption.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(caption.updateInteractions({}), true);
	
	caption.setSize({6, 11});
	ASSERT_EQ(caption.getSize(), (sf::Vector2f{6, 11}));
	ASSERT_EQ(caption.getAreaSize(), (sf::Vector2f{6, 11}));
	
	caption.setPosition({19, 39});
	ASSERT_EQ(caption.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(caption.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	caption.resize({93, 13}, {5, 41});
	ASSERT_EQ(caption.getSize(), (sf::Vector2f{93, 13}));
	ASSERT_EQ(caption.getAreaSize(), (sf::Vector2f{93, 13}));
	ASSERT_EQ(caption.getPosition(), (sf::Vector2f{5, 41}));
	ASSERT_EQ(caption.getAreaPosition(), (sf::Vector2f{5, 41}));
	
	caption.move({2, 5});
	ASSERT_EQ(caption.getPosition(), (sf::Vector2f{7, 46}));
	ASSERT_EQ(caption.getAreaPosition(), (sf::Vector2f{7, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Caption.png"));
}