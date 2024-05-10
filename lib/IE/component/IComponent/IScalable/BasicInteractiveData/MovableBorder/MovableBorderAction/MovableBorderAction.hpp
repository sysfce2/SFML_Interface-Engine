#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"

namespace ie {
	class MovableBorder;
	
	class MovableBorderAction : public virtual IBasicTouchAction<MovableBorder&> {
	public:
		struct Make : public virtual IBasicTouchAction<MovableBorder&>::Make {
			ISMRFloat& value;
			
			Make(ISMRFloat& value);
			
			auto make(BasicActionInitInfo<MovableBorder&> init_info) -> MovableBorderAction* override;
		};
		
		MovableBorderAction(Make&& make, BasicActionInitInfo<MovableBorder&> init_info);
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
	
	protected:
		ActiveTracker tracker_;
		ISMRFloat& value_;
		MovableBorder* object_;
		float offset_;
	};
}


