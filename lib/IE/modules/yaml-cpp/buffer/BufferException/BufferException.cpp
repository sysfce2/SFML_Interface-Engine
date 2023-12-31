#include "BufferException.hpp"

namespace ie {
	BufferNonExistentNestingLevelException::BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, size_t level) :
		BaseYamlException(mark), name_(name), level_(level) {
	}
	
	std::string BufferNonExistentNestingLevelException::get_description() const {
		return
			std::string("An attempt was made to put the Buffer variable '") + name_ +
			std::string("' on a non-existent nesting level, the '") + std::to_string(level_) + std::string("' level");
	}
	
	std::string BufferNonExistentNestingLevelException::get_name() const {
		return name_;
	}
	
	size_t BufferNonExistentNestingLevelException::get_level() const {
		return level_;
	}
	
	BufferVariableNotFoundException::BufferVariableNotFoundException(const std::string& name, const std::string& type) :
		name_(name), type_(type) {
	}
	
	std::string BufferVariableNotFoundException::get_description() const {
		return std::string("Failed to read buffer variable '") + name_ + std::string("' as '") + type_ + std::string("' type");
	}
	
	std::string BufferVariableNotFoundException::get_name() const {
		return name_;
	}
	
	std::string BufferVariableNotFoundException::get_type() const {
		return type_;
	}
	
	YamlBufferVariableNotFoundException::YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception) :
		BaseYamlException(mark), exception_(exception) {
	}
	
	std::string YamlBufferVariableNotFoundException::get_description() const {
		return
			std::string("Failed to read buffer variable '") + exception_.get_name() +
			std::string("' as '") + exception_.get_type() + std::string("' type");
	}
	
	const BufferVariableNotFoundException& YamlBufferVariableNotFoundException::get_exception() const {
		return exception_;
	}
	
	std::string YamlBufferVariableNotFoundException::get_name() const {
		return exception_.get_name();
	}
	
	std::string YamlBufferVariableNotFoundException::get_type() const {
		return exception_.get_type();
	}
}