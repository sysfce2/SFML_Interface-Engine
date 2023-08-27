#pragma once

#include "IE/IComponent/Panel/IPanelInteraction/ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "../../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class DisplayPanelAction : public PanelAction {
	public:
		DisplayPanelAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
	};
	
	template<>
	struct DecodePointer<DisplayPanelAction> {
		static bool decodePointer(const YAML::Node& node, DisplayPanelAction*& displayPanelAction);
	};
}