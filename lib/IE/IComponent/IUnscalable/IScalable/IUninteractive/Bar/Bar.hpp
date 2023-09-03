#pragma once

#include "../OnlyDrawable/OnlyDrawable.hpp"
#include "../OnlyDrawable/Empty/Empty.hpp"
#include "../../../../ILayout/ILayoutBackground/ILayoutBackground.hpp"
#include "../../../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	class Bar : public OnlyDrawable, public virtual ILayoutBackground {
	public:
		struct Make : public virtual IUninteractive::Make, public virtual ILayoutBackground::Make {
			BoxPtr<IUninteractive::Make> background;
			BoxPtr<IUninteractive::Make> strip;
			float offset = 0;
			bool horizontal = true;
			int division = 0;
			
			Make(BoxPtr<IUninteractive::Make>&& background, BoxPtr<IUninteractive::Make>&& strip, float offset = 0, bool horizontal = true);
			
			Make(BoxPtr<IUninteractive::Make>&& background, BoxPtr<IUninteractive::Make>&& strip, int division, float offset = 0, bool horizontal = true);
			
			Bar* make(InitInfo initInfo) override;
		};
		
		Bar(Make&& make, InitInfo initInfo);
		
		explicit Bar(BoxPtr<IUninteractive>&& background, BoxPtr<IUninteractive>&& strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(BoxPtr<IUninteractive>&& background, BoxPtr<IUninteractive>&& strip, int division, float offset = 0, bool horizontal = true);
		
		void init(InitInfo initInfo) override;
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IUninteractive& getBackground() override;
		
		const IUninteractive& getBackground() const override;
		
		Bar* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		BoxPtr<IUninteractive> background;
		BoxPtr<IUninteractive> strip;
		bool horizontal;
		float offset;
		int division;
		float value;
	};
	
	template<>
	struct DecodePointer<Bar> {
		static bool decodePointer(const YAML::Node& node, Bar*& bar);
	};
}
