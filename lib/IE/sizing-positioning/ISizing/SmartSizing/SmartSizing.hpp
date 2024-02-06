#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class SmartSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float target_coefficient = 1;
			float parent_coefficient = 0;
			float addition = 0;
			
			Make(float target_coefficient = 1, float parent_coefficient = 0, float addition = 0);
			
			SmartSizing* make(float normal_size) override;
		};
		
		SmartSizing(Make&& make, float normal_size);
		
		explicit SmartSizing(float target_coefficient = 1, float parent_coefficient = 0, float addition = 0);
		
		float find_size(float parent_size, float target_size) override;
		
		float get_parent_size(float object_size) override;
	
	protected:
		float target_coefficient_;
		float parent_coefficient_;
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::SmartSizing::Make> {
	static orl::Option<ie::SmartSizing::Make> decode(ieml::Node const& node);
};
