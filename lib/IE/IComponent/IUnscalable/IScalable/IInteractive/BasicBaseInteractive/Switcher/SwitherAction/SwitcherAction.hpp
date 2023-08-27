#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public BaseKeyAction {
	public:
		SwitcherAction(PSbool value);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		SwitcherAction* copy() override;
		
	protected:
		PSbool value;
	};
	
	template<>
	struct DecodePointer<SwitcherAction> {
		static bool decodePointer(const YAML::Node& node, SwitcherAction*& switcherAction);
	};
	
}