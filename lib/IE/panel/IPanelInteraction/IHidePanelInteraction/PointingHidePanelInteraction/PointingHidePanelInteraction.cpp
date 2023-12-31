
#include "PointingHidePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	PointingHidePanelInteraction::Make::Make(bool only_on_parent) :
		only_on_parent(only_on_parent) {
	}
	
	PointingHidePanelInteraction* PointingHidePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new PointingHidePanelInteraction{std::move(*this), init_info};
	}
	
	PointingHidePanelInteraction::PointingHidePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		BasePanelInteraction(init_info), only_on_parent_(make.only_on_parent) {
	}
	
	PointingHidePanelInteraction::PointingHidePanelInteraction(bool only_on_parent) : only_on_parent_(only_on_parent) {
	}
	
	void PointingHidePanelInteraction::start(sf::Vector2i) {
	}
	
	void PointingHidePanelInteraction::update(sf::Vector2i mouse_position) {
		sf::Vector2f point_position{static_cast<sf::Vector2f>(mouse_position)};
		if(!panel_->get_parent_processed() && (only_on_parent_ || (!panel_->in_panel(point_position) && panel_->is_free() && !panel_->in_const_panels(point_position)))) {
			panel_manager_->hide_panel(panel_);
		}
	}
	
	void PointingHidePanelInteraction::finish(sf::Vector2i) {
	}
	
	PointingHidePanelInteraction* PointingHidePanelInteraction::copy() {
		return new PointingHidePanelInteraction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<PointingHidePanelInteraction>::decode_pointer(const YAML::Node& node, PointingHidePanelInteraction*& pointing_hide_panel_interaction) {
		bool only_on_parent{false};
		
		if(node["only-on-parent"])
			node["only-on-parent"] >> only_on_parent;
		
		pointing_hide_panel_interaction = new PointingHidePanelInteraction{only_on_parent};
		return true;

	}
	*/
}