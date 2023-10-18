#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/panel/IPanelManager/PanelManagerInterceptor/PanelManagerInterceptor.hpp"

namespace ie {
	class BoxSettable : public Box, public virtual IScalableObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			BoxSettable* make(InitInfo init_info) override;
		};
		
		BoxSettable(Make&& make, InitInfo init_info);
		
		BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size, InitInfo init_info);
		
		BoxSettable(BoxPtr<IScalable>&& object, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void set_object(BoxPtr<IScalable>&& new_object);
		
		void set_object(BoxPtr<IScalable::Make>&& new_object);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		BoxSettable* copy() override;
	
	protected:
		DrawManager draw_manager;
		UpdateManager update_manager;
		sf::RenderWindow* window;
		sf::RenderTarget* render_target;
		InteractionManager interaction_manager;
		InteractionStack* interaction_stack;
		PanelManagerInterceptor panel_manager_interceptor;
		BoxPtr<IScalable> object;
	};
}