#pragma once

#include "../iChangeVariable.hpp"

namespace ui {
	class ChangeVariableBySteppedLine : public IChangeVariable {
	public:
		struct Value {
			float value;
			float size = 0;
		};
	
	protected:
		std::vector<Value> values;
		float size;
	
	public:
		ChangeVariableBySteppedLine(std::vector<Value> values);
		
		float getSize() override;
		
		float operator()(float frame) override;
		
		IChangeVariable* copy() override;
	};
	
	
	template<>
	struct Decode<ChangeVariableBySteppedLine::Value> {
		static bool decode(const YAML::Node& node, ChangeVariableBySteppedLine::Value& value);
	};
	
	
	template<>
	struct DecodePointer<ChangeVariableBySteppedLine> {
		static bool decodePointer(const YAML::Node& node, ChangeVariableBySteppedLine*& brokenLine);
	};
}