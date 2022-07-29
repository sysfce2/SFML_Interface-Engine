#pragma once
#include "../layout.h"
#include "../../iUnscalable/iScalable/iScalable.h"

namespace ui {
	class LayoutWithTwoObjects : public virtual Layout {
	protected:
		IScalable* firstObject;
		IScalable* secondObject;
	
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		explicit LayoutWithTwoObjects(IScalable* firstObject, IScalable* secondObject);
		
		~LayoutWithTwoObjects() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
