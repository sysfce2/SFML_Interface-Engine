#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxMakePermeable : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize = {});
			
			BoxMakePermeable* make(InitInfo initInfo) override;
		};
		
		BoxMakePermeable(Make&& make, InitInfo initInfo);
		
		BoxMakePermeable(BoxPtr<IScalable>&& object, sf::Vector2f minSize);
		
		void init(InitInfo initInfo) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxMakePermeable* copy() override;
		
	protected:
		BoxPtr<IScalable> object;
	};
	
	template<>
	struct DecodePointer<BoxMakePermeable> {
		static bool decodePointer(const YAML::Node& node, BoxMakePermeable*& boxMakePermeable);
	};
}