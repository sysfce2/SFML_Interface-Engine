#pragma once

#include "../IScalableLayout.hpp"
#include "../../../IComponentLayout/IComponentObjectsArray/IComponentObjectsArray.hpp"

namespace ie {
	class IScalableObjectsArray : public virtual IScalableLayout, public virtual IComponentObjectsArray {
	public:
		struct Make : public virtual IScalableLayout::Make, public virtual IComponentObjectsArray::Make {
			IScalableObjectsArray* make(InitInfo init_info) override = 0;
		};
	};
}