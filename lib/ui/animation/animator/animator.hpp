#pragma once

#include "unit/iAnimatorUnit.hpp"
#include "modules/appendix/yaml-cpp/buffer/buffer.hpp"

namespace ui {
	class Animator {
	protected:
		std::vector<IAnimatorUnit*> units;
		std::vector<IAnimatorUnit*> unitsBuff;

	public:
		explicit Animator(std::vector<IAnimatorUnit *> units, PSfloat speed = std::make_shared<Sfloat>(1));

		void update(float time);

		virtual Animator* copy();

		~Animator();
	};

	bool convertPointer(const YAML::Node &node, Animator*& animator);
}