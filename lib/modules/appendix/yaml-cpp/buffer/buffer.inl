//included into buffer.hpp

namespace ui {
	template <typename T, typename... A>
	void Buffer::emplace(const std::string& name, A &&... args) {
		objectsLevels[objectsLevels.size() - 1].try_emplace(name, std::make_shared<T>(args...));
	}
	
	template <typename T>
	void Buffer::insert(const std::string &name, const YAML::Node &node) {
		T* ptr;
		long long level{static_cast<long long>(objectsLevels.size()) - 1};
		
		node >> ptr;
		if(node["level"]) {
			if(node["level"]["relative"]) {
				long long relative;
				node["level"]["relative"] >> relative;
				level -= relative;
			} else {
				if(node.IsScalar()) {
					node["level"] >> level;
				} else {
					node["level"]["absolute"] >> level;
				}
			}
		}
		
		if(level >= 0 && level < objectsLevels.size()) {
			objectsLevels[level].try_emplace(name, ptr);
		} else {
			throw BufferNonExistentNestingLevelException{node.Mark(), name, level};
		}
	}
	
	template <typename T>
	void Buffer::insert(const YAML::Node &node) {
		std::string name;
		node["var"] >> name;
		if(!existAtLevel(name)) {
			insert<T>(name, node);
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
	}
	
	template <typename T>
	std::shared_ptr<T> Buffer::at(const std::string &fullName) {
		std::shared_ptr<T> ptr;
		std::vector<std::string> names{splitByDelimiter(fullName, '.')};
		std::string name{names[0]};
		names.erase(names.begin());
		for(auto level = objectsLevels.rbegin(); level != objectsLevels.rend(); ++level) {
			if(auto object = level->find(name); object != level->end()) {
				ptr = std::dynamic_pointer_cast<T>(getVariable(object->second, names));
				if(ptr.get() != nullptr) {
					return ptr;
				}
			}
		}
		throw BufferVariableNotFoundException{fullName, type_name<T>()};
	}
	
	template <typename T>
	std::shared_ptr<T> Buffer::get(const YAML::Node &node, bool createIfNotExist) {
		std::string name;
		if(node.IsScalar()) {
			node >> name;
		} else {
			node["var"] >> name;
			if(createIfNotExist && !existAtLevel(name)) {
				insert<T>(name, node);
			}
		}
		try {
			return at<T>(name);
		} catch (BufferVariableNotFoundException &exception) {
			throw YamlBufferVariableNotFoundException{node.Mark(), exception};
		}
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, WithVector2<T> *&withVector2) {
		if(node["x"] && node["y"]) {
			withVector2 = new WithVector2<T>(Buffer::get<T>(node["x"]), Buffer::get<T>(node["y"]));
		} else {
			sf::Vector2<typename WithVector2<T>::V> vector;
			
			if(node["vector"]) node["vector"] >> vector;
			
			withVector2 = new WithVector2<T>(vector);
		}
		return true;
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, WithList<T> *&withList) {
		if(node["list"]) {
			std::vector<typename WithList<T>::V> list{node["list"].size()};
			for(int i = 0; i < list.size(); ++i) {
				node["list"][i] >> list[i];
			}
			withList = new WithList<T>{list};
		} else {
			std::vector<std::shared_ptr<T>> list{node["vars"].size()};
			for(int i = 0; i < list.size(); ++i) {
				list[i] = Buffer::get<T>(node["vars"][i]);
			}
			withList = new WithList<T>{list};
		}
		return true;
	}
	
	template <typename T>
	std::shared_ptr<T> atYaml(std::string name) {
		return Buffer::at<T>(name);
	}
	
	template <typename T, typename... A>
	void insertYaml(const std::string& name, A &&... args) {
		Buffer::insert<T>(name, args...);
	}
}