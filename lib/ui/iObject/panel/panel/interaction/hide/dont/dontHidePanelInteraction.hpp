#pragma once

#include "../iHidePanelInteraction.hpp"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"

namespace ui {
	class DontHidePanelInteraction : public IHidePanelInteraction, public EmptyInteraction {
	public:
		DontHidePanelInteraction() = default;
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		DontHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontHidePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, DontHidePanelInteraction*& dontHidePanelInteraction);
	};
}
