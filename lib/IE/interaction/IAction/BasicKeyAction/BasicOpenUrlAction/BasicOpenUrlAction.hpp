#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <string>
#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	template<typename T>
	class BasicOpenUrlAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicOpenUrlAction : public BasicKeyAction<T> {
			std::string url;
			
			BasicOpenUrlAction(const std::string& url);
			
			ie::BasicOpenUrlAction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOpenUrlAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicOpenUrlAction<T>;
		
		BasicOpenUrlAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		explicit BasicOpenUrlAction(const std::string& url);
		
		BasicOpenUrlAction<T>* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		std::string url_;
	};
	
	using OpenUrlAction = BasicOpenUrlAction<>;
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<BasicOpenUrlAction<T> > {
		static bool decode_pointer(const YAML::Node& node, BasicOpenUrlAction<T>*& open_url_interaction);
	};
	*/
	
	bool determine_url(ieml::Node const& node);
}

#include "BasicOpenUrlAction.inl"