namespace ie {
	namespace detail {
		namespace make_system {
			template<typename T>
			BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(
				BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction, uint state
			) : interaction(std::move(interaction)), state(state) {
			}
			
			template<typename T>
			detail::BasicHotkeyInteractionHotkey<T>* BasicHotkeyInteractionHotkey<T>::make(BasicActionInitInfo<T> initInfo) {
				return new detail::BasicHotkeyInteractionHotkey<T>{std::move(*this), initInfo};
			}
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> initInfo) :
			interaction(make.interaction->make(initInfo)), state(state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, uint state) :
			interaction(std::move(interaction)), state(state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(uint state) :
			interaction(nullptr), state(state) {
		}
	}
	
	namespace make_system {
		template<typename T>
		BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename T>
		ie::BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicHotkeyInteraction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> initInfo) :
		hotkeyStates(mapMake(std::move(make.hotkeys), initInfo)), nowHotkeys(nullptr) {
		if(hotkeyStates.size() <= make.state) {
			hotkeyStates.resize(make.state, {});
		}
		nowHotkeys = &hotkeyStates[make.state];
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state) :
		hotkeyStates(std::move(hotkeys)), nowHotkeys(nullptr) {
		if(this->hotkeyStates.size() <= state) {
			this->hotkeyStates.resize(state, {});
		}
		nowHotkeys = &this->hotkeyStates[state];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::init(BasicActionInitInfo<T> initInfo) {
		for(const auto& hotkeyState: hotkeyStates) {
			for(auto& hotkey: hotkeyState) {
				hotkey->interaction->init(initInfo);
			}
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::string) {
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::setHotkeyAction(uint state, typename BasicHotkeyInteraction<T>::Hotkey* hotkeyAction) {
		if(hotkeyStates.size() <= state) {
			hotkeyStates.resize(state, {});
		}
		hotkeyStates[state].emplace_back(hotkeyAction);
	}
	
	template<typename T>
	std::vector<BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> > BasicHotkeyInteraction<T>::getHotkeys(int state) {
		return hotkeyStates[state];
	}
	
	template<typename T>
	BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> BasicHotkeyInteraction<T>::getHotkey(int state, int i) {
		return hotkeyStates[state][i];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::start(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->start(mousePosition);
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::update(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->update(mousePosition);
			if(hotkey->interaction->isPress() && hotkey->state != std::numeric_limits<uint>::max()) {
				finish(mousePosition);
				nowHotkeys = &hotkeyStates[hotkey->state];
				start(mousePosition);
			}
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::finish(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->finish(mousePosition);
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::copy() {
		return new BasicHotkeyInteraction<T>{*this};
	}
	
	template<typename T>
	bool Decode<detail::BasicHotkeyInteractionHotkey<T>*>::decode(const YAML::Node& node, detail::BasicHotkeyInteractionHotkey<T>*& hotkey) {
		hotkey = new detail::BasicHotkeyInteractionHotkey<T>{
			convDef(node["interaction"], BoxPtr<BasicKeysInteraction<T> >{}),
			convDef(node["state"], std::numeric_limits<uint>::max())
		};
		return true;
	}
}