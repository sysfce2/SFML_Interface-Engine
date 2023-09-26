#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxAlternative : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> topObject;
			BoxPtr<IScalable::Make> bottomObject;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& topObject, BoxPtr<IScalable::Make>&& bottomObject, sf::Vector2f minSize = {});
			
			BoxAlternative* make(InitInfo initInfo) override;
		};
		
		BoxAlternative(Make&& make, InitInfo initInfo);
		
		BoxAlternative(BoxPtr<IScalable>&& topObject, BoxPtr<IScalable>&& bottomObject, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxAlternative* copy() override;
		
	protected:
		BoxPtr<IScalable> bottomObject;
		BoxPtr<IScalable> topObject;
	};
	
	template<>
	struct DecodePointer<BoxAlternative> {
		static bool decodePointer(const YAML::Node& node, BoxAlternative*& boxWithAlternativeObject);
	};
}