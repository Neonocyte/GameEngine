#ifndef MOVEMENTSYSTEM
#define MOVEMENTSYSTEM

#include <string>

#include "SDL2/SDL.h"

#include "system.h"
#include "components_master.h"

class MovementSystem : public System{
	public:
		MovementSystem();
		~MovementSystem();
		void update() override;
		
	private:
		
};

#endif