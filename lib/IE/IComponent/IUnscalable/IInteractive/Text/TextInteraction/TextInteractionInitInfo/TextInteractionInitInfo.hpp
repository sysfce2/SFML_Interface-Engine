#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/Interaction/BasicInteractionInitInfo/BasicInteractionInitInfo.hpp"

namespace ie {
	class Text;
	
	using TextInteractionInitInfo = BasicInteractionInitInfo<Text&>;
}
