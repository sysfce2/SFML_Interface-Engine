#pragma once

#include <variant>
#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"

namespace ie {
	template<typename T = std::monostate>
	struct BasicActionInitInfo {
		using AdditionalType = T;
		
		sf::RenderWindow& window;
		sf::RenderTarget& render_target;
		InteractionManager& interaction_manager;
		InteractionStack& interaction_stack;
		IPanelManager& panel_manager;
		T additional;
		
		BasicActionInitInfo(
			sf::RenderWindow& window_,
			sf::RenderTarget& render_target_,
			InteractionManager& interaction_manager_,
			InteractionStack& interaction_stack_,
			IPanelManager& panel_manager_,
			T additional_
		);
		
		BasicActionInitInfo(BasicActionInitInfo<> init_info, T additional_);
		
		BasicActionInitInfo(InitInfo init_info, T additional_);
		
		BasicActionInitInfo<T> copy(sf::RenderWindow& window_) const;
		
		BasicActionInitInfo<T> copy(sf::RenderTarget& render_target_) const;
		
		BasicActionInitInfo<T> copy(InteractionManager& interaction_manager_) const;
		
		BasicActionInitInfo<T> copy(InteractionStack& interaction_stack_) const;
		
		BasicActionInitInfo<T> copy(IPanelManager& panel_manager_) const;
		
		BasicActionInitInfo<T> copy(T additional_) const;
		
		BasicActionInitInfo<> to_general() const;
	};
	
	using ActionInitInfo = BasicActionInitInfo<>;
}

#include "BasicActionInitInfo.inl"