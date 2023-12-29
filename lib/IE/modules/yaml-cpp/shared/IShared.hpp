#pragma once

#include "../yaml.hpp"

namespace ie {
	template<typename T>
	using to_auto = std::remove_const_t<std::remove_reference_t<T> >;
	
	class IShared {
	public:
		virtual ~IShared() = default;
	};
	
	using PIShared = std::shared_ptr<IShared>;
}
