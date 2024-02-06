#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class WhileSwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			int step = 1;
			
			Make(int step = 1);
			
			WhileSwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		};
		
		WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		int size_;
		ISRSize& value_;
		int step_;
	};
}

template<>
struct ieml::Decode<char, ie::WhileSwitchTabsAction::Make> {
	static orl::Option<ie::WhileSwitchTabsAction::Make> decode(ieml::Node const& node);
};
