#include "../../lambda/lambdaInteraction.h"
#include "../mouseInteraction.h"

namespace ui {
	class MouseLambdaInteraction : public MouseInteraction, public LambdaInteraction {
	public:
		static MouseLambdaInteraction debug;
		
		MouseLambdaInteraction(ui::ButtonEvent *leftMouseButton, ui::ButtonEvent *rightMouseButton, void ( *startPointing)(sf::Vector2i mousePosition), void (*finishPointing)(sf::Vector2i mousePosition));
		
		MouseLambdaInteraction* copy() override;
	};
}