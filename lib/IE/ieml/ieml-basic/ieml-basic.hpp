#pragma once

#include <box-ptr/BoxPtr.hpp>
#include <IEML/node.hpp>
#include "IE/ieml/ieml-rttb/ieml-rttb.hpp"
#include "LoadString/LoadString.hpp"

namespace tnl {
	template<typename T_>
	struct TypeName<bp::BoxPtr<T_> > {
		static auto type_name() -> StringView;
	};
	
	template<typename T_>
	struct TypeName<orl::Option<T_> > {
		static auto type_name() -> StringView;
	};
	
	template<typename T_>
	struct TypeName<std::vector<T_> > {
		static auto type_name() -> StringView;
	};
	
	template<typename K_, typename V_>
	struct TypeName<absl::flat_hash_map<K_, V_> > {
		static auto type_name() -> StringView;
	};
	
	template<>
	struct TypeName<ie::LoadString> {
		constexpr static auto type_name = StringView{"String"};
	};
}

namespace ieml {
	template<typename T>
	struct Decode<char, bp::BoxPtr<T> > {
		static auto decode(ieml::Node const& node) -> orl::Option<bp::BoxPtr<T> >;
	};
	
	template<typename T>
	struct Decode<char, orl::Option<T> > {
		static auto decode(ieml::Node const& node) -> orl::Option<orl::Option<T> >;
	};
	
	template<typename T>
	struct Decode<char, std::vector<T> > {
		static auto decode(ieml::Node const& node) -> orl::Option<std::vector<T> >;
	};
	
	template<typename T>
	struct Decode<char, absl::flat_hash_map<std::string, T> > {
		static auto decode(ieml::Node const& node) -> orl::Option<absl::flat_hash_map<std::string, T> >;
	};
	
	template<>
	struct Decode<char, ie::LoadString> {
		static auto decode(ieml::Node const& node) -> orl::Option<ie::LoadString>;
	};
}

#include "ieml-basic.inl"