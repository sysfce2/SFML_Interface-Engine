#pragma once

#include "../ISizing.hpp"

namespace ui {
	class SmartSizing : public ISizing {
	public:
		explicit SmartSizing(float targetCoefficient = 1, float parentCoefficient = 0, float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectSize) override;
		
		SmartSizing* copy() override;
	
	protected:
		float targetCoefficient;
		float parentCoefficient;
		float addition;
	};
	
	template<>
	struct DecodePointer<SmartSizing> {
		static bool decodePointer(const YAML::Node& node, SmartSizing*& smartSizing);
	};
}