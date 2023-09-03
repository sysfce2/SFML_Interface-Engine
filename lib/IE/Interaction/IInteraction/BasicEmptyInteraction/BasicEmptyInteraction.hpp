#pragma once

#include "../IInteraction.hpp"
#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicEmptyInteraction : public virtual IBasicInteraction<T> {
	public:
		struct Make : public virtual IBasicInteraction<T>::Make {
			BasicEmptyInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicEmptyInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicEmptyInteraction();
		
		void start(sf::Vector2i) override;
		
		void update(sf::Vector2i) override;
		
		void finish(sf::Vector2i) override;
		
		BasicEmptyInteraction<T>* copy() override;
	};
	
	using EmptyInteraction = BasicEmptyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicEmptyInteraction<T> > {
		static bool decodePointer(const YAML::Node&, BasicEmptyInteraction<T>*& emptyInteraction);
	};
}

#include "BasicEmptyInteraction.inl"
