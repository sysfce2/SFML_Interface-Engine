#pragma once

#include "../BasicLambdaInteraction/BasicLambdaInteraction.hpp"
#include "../IBasicMouseInteraction/IBasicMouseInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicMouseLambdaInteraction : public BasicLambdaInteraction<T>, public IBasicMouseInteraction<T> {
	public:
		BasicMouseLambdaInteraction(
			BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
			BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
			void (* startPointing)(sf::Vector2i mousePosition),
			void (* finishPointing)(sf::Vector2i mousePosition)
		);
		
		BasicKeyAction<T>& getLeftButtonAction() override;
		
		const BasicKeyAction<T>& getLeftButtonAction() const override;
		
		BasicKeyAction<T>& getRightButtonAction() override;
		
		const BasicKeyAction<T>& getRightButtonAction() const override;
		
		BasicMouseLambdaInteraction<T>* copy() override;
	
		static BasicMouseLambdaInteraction debug;
		
	protected:
		BoxPtr<BasicKeyAction<T> > leftButtonAction;
		BoxPtr<BasicKeyAction<T> > rightButtonAction;
	};
	
	using MouseLambdaInteraction = BasicMouseLambdaInteraction<>;
}

#include "BasicMouseLambdaInteraction.inl"
