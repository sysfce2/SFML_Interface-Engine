#pragma once

#include "../baseComparison/baseSConvertToBoolComparison.hpp"
#include "IE/Modules/yaml-cpp/buffer/buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolGreaterOrEquals : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T fromValue, T compared) override;
	
	public:
		SConvertToBoolGreaterOrEquals(PISValue<T> fromValue, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolGreaterOrEquals<T> > {
		static bool decodePointer(const YAML::Node& node, SConvertToBoolGreaterOrEquals<T>*& sConvertToBoolGreaterOrEquals);
	};
	
	using SConvertFloatToBoolGreaterOrEquals = SConvertToBoolGreaterOrEquals<float>;
	using SConvertIntToBoolGreaterOrEquals = SConvertToBoolGreaterOrEquals<int>;
}

#include "sConvertToBoolGreaterOrEquals.inl"