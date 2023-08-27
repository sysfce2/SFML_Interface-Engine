#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/yaml.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicCloseWindowAction : public BasicBaseKeyAction<T> {
	public:
		BasicCloseWindowAction();
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		BasicCloseWindowAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		sf::RenderWindow* window;
	};
	
	using CloseWindowAction = BasicCloseWindowAction<std::monostate>;
	
	template<typename T>
	struct DecodePointer<BasicCloseWindowAction<T> > {
		static bool decodePointer(const YAML::Node&, BasicCloseWindowAction<T>*& closeWindowAction);
	};
}

#include "BasicCloseWindowAction.inl"