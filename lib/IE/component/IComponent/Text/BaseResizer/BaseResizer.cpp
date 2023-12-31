#include "BaseResizer.hpp"

namespace ie {
	BaseResizer::BaseResizer(float line_spacing, BaseResizer::Align align, BaseResizer::Algorithm algorithm, ResizerInitInfo init_info) :
		characters(&init_info.characters),
		lines(&init_info.lines),
		line_spacing(line_spacing),
		align(align),
		algorithm(algorithm) {
	}
	
	BaseResizer::BaseResizer(float line_spacing, Align align, Algorithm algorithm) : characters(nullptr), lines(nullptr), line_spacing(line_spacing), align(align), algorithm(algorithm) {
	}
	
	void BaseResizer::init(ResizerInitInfo init_info) {
		this->characters = &init_info.characters;
		this->lines = &init_info.lines;
	}
	
	sf::Vector2f BaseResizer::get_min_size() {
		if(algorithm == Algorithm::Console) {
			return get_min_size_console();
		} else if(algorithm == Algorithm::Absolute) {
			return get_min_size_absolute();
		}
		return get_min_size_base();
	}
	
	/*old_yaml_decode_impl
	bool Decode<BaseResizer::Align>::decode(const YAML::Node& node, BaseResizer::Align& align) {
		if(node.as<std::string>() == "left") {
			align = BaseResizer::Align::Left;
		} else if(node.as<std::string>() == "right") {
			align = BaseResizer::Align::Right;
		} else if(node.as<std::string>() == "center") {
			align = BaseResizer::Align::Center;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;

	}
	*/
	
	/*old_yaml_decode_impl
	bool Decode<BaseResizer::Algorithm>::decode(const YAML::Node& node, BaseResizer::Algorithm& align) {
		if(node.as<std::string>() == "base") {
			align = BaseResizer::Algorithm::Base;
		} else if(node.as<std::string>() == "console") {
			align = BaseResizer::Algorithm::Console;
		} else if(node.as<std::string>() == "absolute") {
			align = BaseResizer::Algorithm::Absolute;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;

	}
	*/
}