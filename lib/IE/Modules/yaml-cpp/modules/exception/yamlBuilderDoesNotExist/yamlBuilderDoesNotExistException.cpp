#include "yamlBuilderDoesNotExistException.hpp"

namespace ie {
	YamlBuilderDoesNotExistException::YamlBuilderDoesNotExistException(const std::string& yamlBuilderName) :
		BaseException("BaseYamlBuilder: '" + yamlBuilderName + "' does not exist, but was requested by the module") {}
}