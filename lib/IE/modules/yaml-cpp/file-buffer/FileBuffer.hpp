#pragma once

#include "../yaml.hpp"

namespace ie {
	template<typename T>
	struct LoadFromFile {
		static void load(T& object, std::string name);
	};
	
	template<typename T>
	class FileBuffer {
	public:
		FileBuffer() = default;
		
		static T& get(const std::string& name);
		
		static void set_object(const std::string& name, const std::string& file_path);
		
		static void add_alias(const std::string& name, const std::string& alias);
	
	protected:
		static std::map<std::string, T> objects_;
		static std::map<std::string, T*> aliases_;
	};
	
	using Uint32 = sf::Uint32;
	
	struct SymbolPosition {
		size_t line;
		size_t number;
	};
	
	SymbolPosition read_character_index(const YAML::Node& node, std::basic_ifstream<char32_t>& fin);
	
	std::basic_string<Uint32> u32_string_to_uint32_string(std::basic_string<char32_t> str);
	
	std::basic_string<char32_t> uint32_to_u32string_string(std::basic_string<Uint32> str);
	
	template<>
	struct Decode<std::basic_string<char32_t>> {
		static bool decode(const YAML::Node& node, std::basic_string<char32_t>& string32);
	};
	
	template<>
	struct Decode<sf::String> {
		static bool decode(const YAML::Node& node, sf::String& sf_string);
	};
	
	template<>
	struct Decode<sf::Texture*> {
		static bool decode(const YAML::Node& node, sf::Texture*& texture);
	};
	
	template<>
	struct Decode<sf::Font*> {
		static bool decode(const YAML::Node& node, sf::Font*& font);
	};
	
#ifdef IE_ImageMagick_FOUND
	template<>
	struct LoadFromFile<std::vector<sf::Texture>> {
		static void load(std::vector<sf::Texture>& object, std::string name);
	};
	
	template<>
	struct Decode<std::vector<sf::Texture>*> {
		static bool decode(const YAML::Node& node, std::vector<sf::Texture>*& video);
	};
#endif
}

#include "FileBuffer.inl"
