#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	enum class Location {
		Origin,
		Center,
		End
	};
	
	/*old_yaml_decode
	template<>
	struct Decode<Location> {
		static bool decode(const YAML::Node& node, Location& location);
	};
	*/
}