#pragma once

#include <variant>
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"

namespace ie {
	class UpdateManager;
	
	template<typename T = std::monostate>
	struct BasicActionInitInfo {
		using AdditionalType = T;
		
		sf::RenderWindow& window;
		sf::RenderTarget& render_target;
		DynBuffer& dyn_buffer;
		KeyHandler& key_handler;
		UpdateManager& update_manager;
		InteractionManager& interaction_manager;
		IPanelManager& panel_manager;
		T additional;
		
		BasicActionInitInfo(
			sf::RenderWindow& window_,
			sf::RenderTarget& render_target_,
			DynBuffer& dyn_buffer_,
			KeyHandler& key_handler_,
			UpdateManager& update_manager_,
			InteractionManager& interaction_manager_,
			IPanelManager& panel_manager_,
			T additional_
		);
		
		BasicActionInitInfo(BasicActionInitInfo<> init_info, T additional_);
		
		BasicActionInitInfo(InitInfo init_info, T additional_);
		
		auto copy(sf::RenderWindow& window_) const -> BasicActionInitInfo<T>;
		
		auto copy(sf::RenderTarget& render_target_) const -> BasicActionInitInfo<T>;
		
		auto copy(DynBuffer& dyn_buffer_) const -> BasicActionInitInfo<T>;
		
		auto copy(KeyHandler& key_handler) const -> BasicActionInitInfo<T>;
		
		auto copy(UpdateManager& update_manager_) const -> BasicActionInitInfo<T>;
		
		auto copy(InteractionManager& interaction_manager_) const -> BasicActionInitInfo<T>;
		
		auto copy(IPanelManager& panel_manager_) const -> BasicActionInitInfo<T>;
		
		auto copy(T additional_) const -> BasicActionInitInfo<T>;
		
		auto to_general() const -> BasicActionInitInfo<>;
	};
	
	using ActionInitInfo = BasicActionInitInfo<>;
}

#include "BasicActionInitInfo.inl"
