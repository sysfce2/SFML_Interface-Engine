#include "ClickDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	ClickDisplayPanelInteraction::Make::Make(Key key) : key(key) {
	}
	
	auto ClickDisplayPanelInteraction::Make::make(PanelActionInitInfo init_info) -> ClickDisplayPanelInteraction* {
		return new ClickDisplayPanelInteraction{std::move(*this), init_info};
	}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		ClickPanelInteraction(make_box_ptr<DisplayPanelAction::Make>(), make.key, init_info) {
	}
	
	auto ClickDisplayPanelInteraction::start(sf::Vector2i) -> void {
		dynamic_cast<PanelAction&>(*action_).get_panel()->set_parent_processed(true);
	}
	
	auto ClickDisplayPanelInteraction::finish(sf::Vector2i mouse_position) -> void {
		BasicOneKeyInteraction<Panel&>::finish(mouse_position);
		dynamic_cast<PanelAction&>(*action_).get_panel()->set_parent_processed(false);
	}
}

auto ieml::Decode<char, ie::ClickDisplayPanelInteraction::Make>::decode(
	ieml::Node const& node
) -> orl::Option<ie::ClickDisplayPanelInteraction::Make> {
	return {{node.at("key").except().as<ie::Key>().except()}};
}
