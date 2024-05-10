#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public virtual IBasicTouchAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual IBasicTouchAction<BoxSwitcherTabs&>::Make {
			MakeDyn<ISMRSize> value;
			
			Make(MakeDyn<ISMRSize> value);
			
			auto make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info);
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
		
	protected:
		ActiveTracker tracker_;
		ISMRSize& value_;
		BoxSwitcherTabs* switcher_tabs_;
	};
}