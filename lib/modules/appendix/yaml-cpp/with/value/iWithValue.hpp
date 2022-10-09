#pragma once
#include "../iWith.hpp"

namespace ui {
	template<typename T>
	class IWithValue : public IWith {
	public:
		virtual const T& getValue() const = 0;
		
		virtual void setValue(const T& value) = 0;
	};
	
	typedef IWithValue<bool> IWithB;
	typedef IWithValue<float> IWithF;
	typedef IWithValue<int> IWithI;
	typedef IWithValue<unsigned> IWithU;
}