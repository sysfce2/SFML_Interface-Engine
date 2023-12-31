#pragma once

#include <vector>
#include "../IAnimatorUnit.hpp"
#include "../../../IChangeVariable/IChangeVariable.hpp"
#include "IE/modules/yaml-cpp/buffer/Buffer.hpp"

namespace ie {
	class Animation : public virtual IAnimatorUnit {
	public:
		struct Variable {
			PSfloat animation_variable;
			std::vector<IChangeVariable*> change_variables;
			size_t active_changer = 0;
			float time_start_changer = 0;
			
			Variable(PSfloat animation_variable = {}, std::vector<IChangeVariable*> change_variables = {});
			
			Variable copy();
		};
	
		explicit Animation(std::vector<Variable> animation_variables, PSfloat speed = PSfloat{nullptr}, std::vector<IAnimatorUnit*> next_units = {});
		
		void set_speed(PSfloat speed) override;
		
		void restart() override;
		
		std::vector<IAnimatorUnit*> update(float time) override;
		
		void set_next_units(std::vector<IAnimatorUnit*> next_unit);
		
		void add_next_units(IAnimatorUnit* next_unit);
		
		Animation* copy() override;
		
		~Animation();
	
	protected:
		std::vector<IAnimatorUnit*> next_units_;
		std::vector<IAnimatorUnit*> next_units_buff_;
		std::vector<Variable> animation_variables_;
		std::vector<Variable*> animation_updatable_variables_;
		PSfloat speed_;
	};
	
	/*old_yaml_decode
	template<>
	struct Decode<Animation::Variable> {
		static bool decode(const YAML::Node& node, Animation::Variable& animation_unit);
	};
	*/
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<Animation> {
		static bool decode_pointer(const YAML::Node& node, Animation*& animation);
	};
	*/
}