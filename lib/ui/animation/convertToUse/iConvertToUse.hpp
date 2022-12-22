#pragma once

namespace ui {
	template<typename T>
	class IConvertToUse {
	protected:
		virtual T convert(float value) = 0;

	public:
		T operator() (float value) {
			return convert(value);
		}
	};
}