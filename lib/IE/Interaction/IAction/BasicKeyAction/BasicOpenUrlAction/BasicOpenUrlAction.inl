#include "../../../../Modules/openUrl/openUrl.hpp"

namespace ie {
	template<typename T>
	BasicOpenUrlAction<T>::Make::Make(const std::string& url) : url(url) {
	}
	
	template<typename T>
	BasicOpenUrlAction<T>* BasicOpenUrlAction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicOpenUrlAction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	BasicOpenUrlAction<T>::BasicOpenUrlAction(Make&& make, BasicActionInitInfo<T>) :
		url(std::move(make.url)) {
	}
	
	template<typename T>
	BasicOpenUrlAction<T>::BasicOpenUrlAction(const std::string& url) : url(url) {
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::startPressed() {
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::stopPressed() {
		openUrl(url);
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::whilePressed() {
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::whileNotPressed() {
	}
	
	template<typename T>
	BasicOpenUrlAction<T>* BasicOpenUrlAction<T>::copy() {
		return new BasicOpenUrlAction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicOpenUrlAction<T> >::decodePointer(const YAML::Node& node, BasicOpenUrlAction<T>*& openUrlInteraction) {
		openUrlInteraction = new BasicOpenUrlAction<T>{
			(node.IsScalar() ? node : node["url"]).as<std::string>()
		};
		return true;
	}
}