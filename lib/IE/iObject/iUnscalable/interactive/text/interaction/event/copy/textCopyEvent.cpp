#include <codecvt>
#include "textCopyEvent.hpp"
#include "IE/iObject/iUnscalable/interactive/text/text.hpp"
#include "modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	void TextCopyEvent::startPressed() {
		sf::Clipboard::setString(u32stringToUint32String(text->getSelectionText()));
	}
	
	void TextCopyEvent::stopPressed() {
	}
	
	void TextCopyEvent::whilePressed() {
	}
	
	void TextCopyEvent::whileNotPressed() {
	}
	
	TextCopyEvent* TextCopyEvent::copy() {
		return new TextCopyEvent{};
	}
	
	bool DecodePointer<TextCopyEvent>::decodePointer(const YAML::Node&, TextCopyEvent*& textCopyEvent) {
		textCopyEvent = new TextCopyEvent{};
		return true;
	}
}