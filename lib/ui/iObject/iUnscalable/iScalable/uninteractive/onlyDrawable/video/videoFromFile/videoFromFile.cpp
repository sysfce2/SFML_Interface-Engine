#include "videoFromFile.hpp"

namespace ui {
	VideoFromFile::VideoFromFile(std::vector<sf::Texture> video, PSCoefficient viewingProgress) :
		bufferTexture(video), viewingProgress(viewingProgress), sizeVideo(video[0].getSize()) {
		viewingProgress->addSetter([=](float viewingProgress) {
			setCurrentFrame(viewingProgress);
		});
		sprite.setTexture(bufferTexture[0]);
	}
	
	void VideoFromFile::setCurrentFrame(float viewingProgress) {
		if(viewingProgress >= 1) {
			sprite.setTexture(bufferTexture[bufferTexture.size()]);
			return;
		}
		if(viewingProgress <= 0) {
			sprite.setTexture(bufferTexture[0]);
			return;
		}
		sprite.setTexture(bufferTexture[bufferTexture.size() * viewingProgress]);
	}
	
	void VideoFromFile::draw() {
		renderTarget->draw(sprite);
	}
	
	void VideoFromFile::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		sprite.setPosition(position);
		sprite.setScale(size / sf::Vector2f{sizeVideo});
	}
	
	sf::Vector2f VideoFromFile::getAreaPosition() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f VideoFromFile::getAreaSize() const {
		return size;
	}
	
	sf::Vector2f VideoFromFile::getMinSize() const {
		return {0, 0};
	}
	
	sf::Vector2f VideoFromFile::getNormalSize() const {
		return sf::Vector2f{sizeVideo};
	}
	
	VideoFromFile* VideoFromFile::copy() {
		return new VideoFromFile{*this};
	}
}