#pragma once

#include "IE/IDrawable/DrawManager/DrawManager.hpp"
#include "IE/IUpdatable/UpdateManager/UpdateManager.hpp"
#include "IE/Interaction/InteractionStack/InteractionStack.hpp"
#include "IE/Interaction/InteractionManager/InteractionManager.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "IE/Animation/AnimationManager/AnimationManager.hpp"
#include "IE/Make/make.hpp"
#include "IE/Utils/Reduce/Reduce.hpp"
#include "IE/Utils/Vector/Vector.hpp"
#include "IE/Utils/Vector2/Vector2.hpp"
#include "InitInfo/InitInfo.hpp"

using uint = unsigned;

namespace ie {
	using namespace bp;
	
	class Panel;
	
	class PanelManager;
	
	class IPanelManager;
	
	class IComponent {
	public:
		struct Make {
			virtual IComponent* make(InitInfo initInfo) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~IComponent() = default;
		
		virtual void init(InitInfo initInfo) = 0;
		
		virtual void setPosition(sf::Vector2f position);
		
		virtual void move(sf::Vector2f position);
		
		virtual void setSize(sf::Vector2f size);
		
		virtual sf::Vector2f getAreaPosition() const = 0;
		
		virtual sf::Vector2f getPosition() const;
		
		virtual sf::Vector2f getAreaSize() const = 0;
		
		virtual sf::Vector2f getSize() const;
		
		virtual sf::Vector2f getMinSize() const = 0;
		
		virtual sf::Vector2f getNormalSize() const = 0;
		
		virtual bool inArea(sf::Vector2f pointPosition);
		
		virtual bool in(sf::Vector2f pointPosition);
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual IComponent* copy() = 0;
		
		static void drawDebug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& renderTarget, uint hue);
		
		virtual void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
}