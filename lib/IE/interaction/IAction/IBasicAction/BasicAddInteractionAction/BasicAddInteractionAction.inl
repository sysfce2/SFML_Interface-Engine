namespace ie {
	namespace make_system {
		template<typename T>
		BasicAddInteractionAction<T>::BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
			interaction(std::move(interaction)) {
		}
		
		template<typename T>
		auto BasicAddInteractionAction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicAddInteractionAction<T>* {
			return new ie::BasicAddInteractionAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> init_info) :
		interaction_manager_(&init_info.interaction_manager), interaction_(make.interaction->make(init_info)) {
	}
	
	template<typename T>
	auto BasicAddInteractionAction<T>::get_interaction() -> IBasicInteraction<T>& {
		return *interaction_;
	}
	
	template<typename T>
	auto BasicAddInteractionAction<T>::start_pressed() -> void {
		interaction_manager_->add_interaction(*interaction_);
	}
	
	template<typename T>
	auto BasicAddInteractionAction<T>::stop_pressed() -> void {
		interaction_manager_->delete_interaction(*interaction_);
	}
	
	template<typename T>
	auto BasicAddInteractionAction<T>::while_pressed() -> void {
	}
	
	template<typename T>
	auto BasicAddInteractionAction<T>::while_not_pressed() -> void {
	}
	
	template<typename T>
	auto BasicAddInteractionAction<T>::finish() -> void {
		interaction_manager_->delete_interaction(*interaction_);
	}
}