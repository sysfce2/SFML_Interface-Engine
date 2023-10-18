#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxScroll/BoxScroll.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, BoxScroll) {
	InitInfoData data{{100, 100}};
	
	ie::BoxScroll box_scroll{
		ie::BoxScroll::Make{
			ie::make_box_ptr<ie::IComponent::Make, ie::FullColor::Make>(sf::Color::Green),
			std::make_shared<ie::SRVec2f>(sf::Vector2f{})
		},
		data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &box_scroll);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_scroll.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_scroll.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_scroll.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_scroll.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_scroll.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_scroll.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_scroll.update_interactions({}), true);
	
	box_scroll.set_size({5, 11});
	ASSERT_EQ(box_scroll.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_scroll.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_scroll.set_position({19, 39});
	ASSERT_EQ(box_scroll.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_scroll.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_scroll.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_scroll.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_scroll.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_scroll.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_scroll.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_scroll.move({10, 5});
	ASSERT_EQ(box_scroll.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_scroll.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxScroll.png"));
}