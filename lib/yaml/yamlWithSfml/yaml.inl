//included into yaml.hpp

template <typename T>
std::enable_if_t<!std::is_constructible_v<T, const YAML::Node &>, void> operator>>(const YAML::Node &node, T &value) {
	value = node.as<T>();
}

template <typename T>
std::enable_if_t<std::is_constructible_v<T, const YAML::Node &>, void> operator>>(const YAML::Node &node, T &value) {
	value = T{node};
}

template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T> &first, const sf::Vector2<T> &second) {
	return {first.x * second.x, first.y * second.y};
}

template <typename T>
sf::Vector2<T> operator/(const sf::Vector2<T> &first, const sf::Vector2<T> &second) {
	return {first.x / second.x, first.y / second.y};
}

template<typename T>
void operator >>(const YAML::Node& node, sf::Vector2<T>& vector) {
	vector.x = node[0].as<T>();
	vector.y = node[1].as<T>();
}

template <typename T>
void operator>>(const YAML::Node &node, std::vector<T> &vector) {
	for(const auto &item : node) {
		vector.resize(vector.size() + 1);
		item >> vector[vector.size() - 1];
	}
}

template <typename T>
void operator>>(const YAML::Node &node, sf::Rect<T> &rect) {
	sf::Vector2<T> position;
	sf::Vector2<T> size;
	node["position"] >> position;
	node["size"] >> size;
	rect = sf::Rect<T>{position, size};
}