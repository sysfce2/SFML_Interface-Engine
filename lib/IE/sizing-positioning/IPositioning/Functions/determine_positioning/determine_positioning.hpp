#pragma once

#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	auto determine_positioning(ieml::Node const& node) -> orl::Option<std::string>;
}