#include "relativeNormalSizing.hpp"

namespace ui {
	RelativeNormalSizing::RelativeNormalSizing() : normalSize(0) {}
	
	void RelativeNormalSizing::init(float normalSize) {
		this->normalSize = normalSize;
	}
	
	float RelativeNormalSizing::findSize(float, float) {
		return this->normalSize;
	}
	
	void RelativeNormalSizing::copy(RelativeNormalSizing *relativeNormalSizing) {
		relativeNormalSizing->normalSize = this->normalSize;
	}
	
	RelativeNormalSizing *RelativeNormalSizing::copy() {
		RelativeNormalSizing* normalSizeSizing{new RelativeNormalSizing{}};
		RelativeNormalSizing::copy(normalSizeSizing);
		return normalSizeSizing;
	}
	
	RelativeNormalSizing *RelativeNormalSizing::createFromYaml(const YAML::Node &) {
		return new RelativeNormalSizing{};
	}
	
	Sizing *createSize() {
		return new RelativeNormalSizing{};
	}
}