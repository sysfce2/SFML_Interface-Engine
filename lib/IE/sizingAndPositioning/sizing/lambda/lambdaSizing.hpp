#pragma once

#include "../iSizing.hpp"
#include <functional>

namespace ui {
	class LambdaSizing : public ISizing {
	public:
		using FindSizeFunc = std::function<float(float parentSize, float targetSize, float normalSize)>;
		using MinSizeFunc = std::function<float(float objectMinSize)>;
	
		explicit LambdaSizing(FindSizeFunc findSizeFunc, MinSizeFunc minSizeFunc);
		
		void init(float normalSize) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectMinSize) override;
		
		LambdaSizing* copy() override;
	
	protected:
		FindSizeFunc findSizeFunc;
		MinSizeFunc minSizeFunc;
		float normalSize;
	};
}