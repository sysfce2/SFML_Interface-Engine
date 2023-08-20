#pragma once

#include <vector>
#include "../iUpdatable/iUpdatable.hpp"

namespace ui {
	class UpdateManager : public IUpdatable {
	public:
		UpdateManager() = default;
		
		std::size_t size();
		
		IUpdatable& get(std::size_t index);
		
		void add(IUpdatable& updatable);
		
		void clear();
		
		void update() override;
	
	protected:
		std::vector<IUpdatable*> updatable;
	};
}