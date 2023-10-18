#include "BufferException.hpp"

namespace ie {
	BufferNonExistentNestingLevelException::BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, std::size_t level) :
		BaseYamlException(mark, std::string("An attempt was made to put the Buffer variable '") + name + std::string("' on a non-existent nesting level, the '") + std::to_string(level) + std::string("' level")),
		name(name), level(level) {
	}
	
	std::string BufferNonExistentNestingLevelException::get_name() const {
		return name;
	}
	
	std::size_t BufferNonExistentNestingLevelException::get_level() const {
		return level;
	}
	
	BufferVariableNotFoundException::BufferVariableNotFoundException(const std::string& name, const std::string& type) :
		BaseException(std::string("Failed to read buffer variable '") + name + std::string("' as '") + type + std::string("' type")),
		name(name), type(type) {
	}
	
	std::string BufferVariableNotFoundException::get_name() const {
		return name;
	}
	
	std::string BufferVariableNotFoundException::get_type() const {
		return type;
	}
	
	YamlBufferVariableNotFoundException::YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception) :
		BaseYamlException(mark, std::string("Failed to read buffer variable '") + exception.get_name() + std::string("' as '") + exception.get_type() + std::string("' type")),
		exception(exception) {
	}
	
	BufferVariableNotFoundException YamlBufferVariableNotFoundException::get_exception() const {
		return exception;
	}
	
	std::string YamlBufferVariableNotFoundException::get_name() const {
		return exception.get_name();
	}
	
	std::string YamlBufferVariableNotFoundException::get_type() const {
		return exception.get_type();
	}
}