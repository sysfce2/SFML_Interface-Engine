#include "ChangeVariableBySinusoid.hpp"

namespace ie {
	ChangeVariableBySinusoid::ChangeVariableBySinusoid(float size, float a, float b, float c, float d) : a(a), b(b), c(c), d(d), size(size) {
	}
	
	float ChangeVariableBySinusoid::getSize() {
		return size;
	}
	
	float ChangeVariableBySinusoid::operator()(float frame) {
		return a + (b * std::sin((c * frame) + d));
	}
	
	IChangeVariable* ChangeVariableBySinusoid::copy() {
		return new ChangeVariableBySinusoid{size, a, b, c, d};
	}
	
	
	bool DecodePointer<ChangeVariableBySinusoid>::decodePointer(const YAML::Node& node, ChangeVariableBySinusoid*& changeVariableBySinusoid) {
		changeVariableBySinusoid = new ChangeVariableBySinusoid{
			node["size"].as<float>(),
			convDef(node["a"], convDef(node["offset-OY"], 0.f)),
			convDef(node["b"], convDef(node["amplitude"], 1.f)),
			convDef(node["c"], convDef(node["frequency"], 1.f)),
			convDef(node["d"], convDef(node["offset-OX"], 0.f)),
		};
		
		return true;
	}
}