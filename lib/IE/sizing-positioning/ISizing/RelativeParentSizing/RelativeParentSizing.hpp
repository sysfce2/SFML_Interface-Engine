#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class RelativeParentSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float addition = 0;
			
			Make(float addition = 0);
			
			RelativeParentSizing* make(float normal_size) override;
		};
		
		RelativeParentSizing(Make&& make, float normal_size);
		
		explicit RelativeParentSizing(float addition = 0);
		
		float find_size(float parent_size, float) override;
		
		float get_parent_size(float object_size) override;
		
	protected:
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::RelativeParentSizing::Make> {
	static orl::Option<ie::RelativeParentSizing::Make> decode(ieml::Node const& node);
};
