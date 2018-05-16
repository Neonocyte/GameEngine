#ifndef GRAPHICSYSTEM
#define GRAPHICSYSTEM

#include <string>

#include "SDL2/SDL.h"

#include "system.h"
#include "components_master.h"

class GraphicsSystem : public System{
	public:
		GraphicsSystem(SDL_Window *mainWindow);
		~GraphicsSystem();
		void update() override;
		
	private:
		SDL_Renderer* mainRenderer = nullptr;
};

#endif