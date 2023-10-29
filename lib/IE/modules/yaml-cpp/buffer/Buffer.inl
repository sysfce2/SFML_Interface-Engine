//included into buffer.hpp

#include "../shared/ISValue/SValue/SValue.hpp"

namespace ie {
	template<typename T, typename... A>
	void Buffer::emplace(const std::string& name, A&& ... args) {
		objects_levels_[objects_levels_.size() - 1].try_emplace(name, std::make_shared<T>(args...));
	}
	
	template<typename T>
	void Buffer::insert(const std::string& name, const YAML::Node& node) {
		if(objects_levels_.empty()) {
			throw BufferNonExistentNestingLevelException{node.Mark(), name, 0};
		}
		
		size_t level{objects_levels_.size() - 1};
		
		if(node["level"]) {
			if(node["level"]["relative"]) {
				auto relative{node["level"]["relative"].as<size_t>()};
				
				if(level < relative) {
					throw BufferNonExistentNestingLevelException{node.Mark(), name, 0};
				}
				
				level -= relative;
			} else {
				if(node.IsScalar()) {
					level = node["level"].as<size_t>();
				} else {
					level = node["level"]["absolute"].as<size_t>();
				}
			}
		}
		
		if(level < objects_levels_.size()) {
			objects_levels_[level].try_emplace(name, node.as<T*>());
		} else {
			throw BufferNonExistentNestingLevelException{node.Mark(), name, level};
		}
	}
	
	template<typename T>
	void Buffer::insert(const YAML::Node& node) {
		auto name{node["var"].as<std::string>()};
		if(!exist_at_level(name)) {
			insert<T>(name, node);
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
	}
	
	template<typename T>
	std::shared_ptr<T> Buffer::at(const std::string& full_name) {
		std::shared_ptr<T> ptr;
		std::vector<std::string> names{split_by_delimiter(full_name, '.')};
		std::string name{names[0]};
		names.erase(names.begin());
		for(auto level = objects_levels_.rbegin(); level != objects_levels_.rend(); ++level) {
			if(auto object = level->find(name); object != level->end()) {
				ptr = std::dynamic_pointer_cast<T>(get_variable(object->second, names));
				if(ptr.get() != nullptr) {
					return ptr;
				}
			}
		}
		throw BufferVariableNotFoundException{full_name, type_name<T>()};
	}
	
	template<typename T>
	std::shared_ptr<T> Buffer::get(const YAML::Node& node, bool create_if_not_exist) {
		std::string name;
		if(node.IsScalar()) {
			name = node.as<std::string>();
		} else {
			name = node["var"].as<std::string>();
			if(create_if_not_exist && !exist_at_level(name)) {
				insert<T>(name, node);
			}
		}
		try {
			return at<T>(name);
		} catch(BufferVariableNotFoundException& exception) {
			throw YamlBufferVariableNotFoundException{node.Mark(), exception};
		}
	}
	
	template<typename T>
	std::shared_ptr<T> at_s_value(std::string name) {
		return Buffer::at<T>(name);
	}
	
	template<typename T, typename... A>
	void emplace_s_value(const std::string& name, A&& ... args) {
		Buffer::insert<T>(name, args...);
	}
	
	template<typename T>
	std::shared_ptr<T> get_s_value(const YAML::Node& node, bool create_if_not_exist) {
		return Buffer::get<T>(node, create_if_not_exist);
	}
}