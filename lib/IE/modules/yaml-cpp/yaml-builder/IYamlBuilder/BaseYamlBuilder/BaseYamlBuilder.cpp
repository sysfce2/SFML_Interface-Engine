#include "BaseYamlBuilder.hpp"

namespace ie::detail {
	std::unordered_map<std::string, BaseYamlBuilder*> yaml_builders;
}