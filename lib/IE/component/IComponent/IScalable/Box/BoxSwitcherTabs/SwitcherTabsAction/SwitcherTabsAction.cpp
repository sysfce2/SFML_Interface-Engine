#include "SwitcherTabsAction.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ie {
	SwitcherTabsAction::Make::Make(MakeDyn<ISRSize> value) : value(std::move(value)) {
	}
	
	SwitcherTabsAction* SwitcherTabsAction::Make::make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) {
		return new SwitcherTabsAction{std::move(*this), init_info};
	}
	
	SwitcherTabsAction::SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info) :
		value_(make.value.make(init_info.dyn_buffer)), switcher_tabs_(&init_info.additional) {
	}
	
	void SwitcherTabsAction::start_pressed() {
	}
	
	void SwitcherTabsAction::stop_pressed() {
		value_.set(switcher_tabs_->get_tab(sf::Vector2f(mouse_position_)));
	}
	
	void SwitcherTabsAction::while_pressed() {
	}
	
	void SwitcherTabsAction::while_not_pressed() {
	}
}