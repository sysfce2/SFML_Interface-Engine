#pragma once
#include <vector>

#include "../iLayer.h"
#include "../../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class LayerWithBorderHorizontal : public ILayer {
	protected:
		std::vector<IFlat *> objects;
		std::vector<float> boundsHorizontal;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
	public:
		LayerWithBorderHorizontal(std::vector<IFlat *> objects, std::vector<float> bounds, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorderHorizontal(std::vector<IFlat *> objects, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorderHorizontal(IFlat *first, IFlat *second, float bound = 0.5f, sf::Vector2f minSize = {0, 0});
		
		~LayerWithBorderHorizontal() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithBorderHorizontal* copy() override;
	};
	
	typedef LayerWithBorderHorizontal LayerWBoundH;
	typedef LayerWithBorderHorizontal LWBH;
}