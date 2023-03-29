#pragma once

#include <vector>
#include "../iAnimatorUnit.hpp"
#include "../../../variables/iAnimationVariable.hpp"
#include "../../../changeVariable/iChangeVariable.hpp"

namespace ui {
	class Animation : public IAnimatorUnit{
	public:
		struct Variable{
			IAnimationVariable* animationVariable;
			std::vector<IChangeVariable*> changeVariables;
			unsigned int activeChanger = 0;
			float timeStartChanger = 0;

			Variable(IAnimationVariable *animationVariable = nullptr, std::vector<IChangeVariable *> changeVariables = {});

			Variable copy();
		};

	protected:
		std::vector<IAnimatorUnit*> nextUnits;
		std::vector<IAnimatorUnit*> nextUnitsBuff;
		std::vector<Variable> animationVariables;
		std::vector<Variable*> animationUpdatableVariables;
		float speed;

	public:
		explicit Animation(std::vector<Variable> animationVariables, std::vector<IAnimatorUnit *> nextUnits = {}, float speed = 1);

		void restart() override;

		std::vector<IAnimatorUnit*> update(float time) override;

		void setNextUnits(std::vector<IAnimatorUnit*> nextUnit);

		void addNextUnits(IAnimatorUnit* nextUnit);

		Animation* copy() override;

		~Animation();
	};

	template<>
	bool convert(const YAML::Node &node, Animation::Variable& animationUnit);

	bool convertPointer(const YAML::Node &node, Animation*& animation);
}