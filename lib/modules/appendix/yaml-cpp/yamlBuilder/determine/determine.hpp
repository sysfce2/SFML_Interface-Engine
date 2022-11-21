#pragma once
#include "../yamlBuilder.hpp"

namespace ui {
	namespace detail {
		struct YamlArg {
			std::string name;
			YAML::NodeType::value type{YAML::NodeType::Undefined};
			[[nodiscard]] bool present(const YAML::Node& node) const;
		};
	}
	
	bool determine(const YAML::Node& node, std::initializer_list<detail::YamlArg> args);
	
	bool determine(const YAML::Node& node, std::initializer_list<detail::YamlArg> args, std::initializer_list<detail::YamlArg> optArgs);
}