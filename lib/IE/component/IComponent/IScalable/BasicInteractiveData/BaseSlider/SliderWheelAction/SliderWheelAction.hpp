#pragma once

#include "IE/interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/interaction/IAction/WheelAction/BaseWheelAction/BaseWheelAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderWheelAction : public BaseWheelAction {
	public:
		enum class Relativity {
			RelationArea,
			RelationSlider
		};
	
		struct Make {
			bool horizontal = false;
			Relativity relativity = Relativity::RelationSlider;
			sf::Vector2f sensitivity = {0.2f, 0.2f};
			
			Make(bool horizontal = false, Relativity relativity = Relativity::RelationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
			
			SliderWheelAction* make(BasicActionInitInfo<BaseSlider&> init_info);
		};
		
		SliderWheelAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		explicit SliderWheelAction(bool horizontal = false, Relativity relativity = Relativity::RelationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
		
		void set_slider(BaseSlider& slider);
		
		void start_pressed(sf::Vector2i mouse_position, int value) override;
		
		void stop_pressed(sf::Vector2i mouse_position, int value) override;
		
		void while_pressed(sf::Vector2i mouse_position, int value) override;
		
		void while_not_pressed(sf::Vector2i mouse_position, int value) override;
		
		SliderWheelAction* copy() override;
		
	protected:
		BaseSlider* slider_;
		sf::Vector2f sensitivity_;
		bool horizontal_;
		bool relativity_;
	};
	
	/*old_yaml_decode
	template<>
	struct Decode<SliderWheelAction::Relativity> {
		static bool decode(const YAML::Node& node, SliderWheelAction::Relativity& relativity);
	};
	*/
}