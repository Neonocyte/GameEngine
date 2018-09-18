#include "../include/graphics_system.h"


//TODO: initialization needs proper error logging.
GraphicsSystem::GraphicsSystem(SDL_Window *mainWindow){
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if(mainRenderer == nullptr){
		std::cout << "Renderer could not initialize. SDL Error: " << std::string(SDL_GetError()) << std::endl;
		//logError("Renderer could not initialize. SDL Error: " + std::string(SDL_GetError()));
	}else{
		SDL_SetRenderDrawColor(mainRenderer, 0xF5, 0xE3, 0xAD, 0xFF);
		ResourceManager::setRenderer(mainRenderer);
		
		int imgFlags = IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags)){
			std::cout << "SDL_image could not initialize. SDL_image Error: " << IMG_GetError() << std::endl;
			//logError("SDL_image could not initialize. SDL_image Error: " + std::string(IMG_GetError()));
		}
	}
}

GraphicsSystem::~GraphicsSystem(){
	SDL_DestroyRenderer(mainRenderer);
}

void GraphicsSystem::update(){
	SDL_RenderClear(mainRenderer);
	
	//std::cout << "updating graphics" << std::endl;
	
	for(auto entity : Entity::entityVector){
		//TODO: Get draw components and update
		LocationComponent *locationComp;
		GraphicsComponent *graphicsComp;
		
		
		if((locationComp = static_cast<LocationComponent*>(entity->getComponent(CG_Location))) && (graphicsComp = static_cast<GraphicsComponent*>(entity->getComponent(CG_Graphics)))){
			//std::cout << "starting draw" << std::endl;
			Location entityLoc = locationComp->getLocation();
			//std::cout << "location retrieved: " << entityLoc.x << " " << entityLoc.y << std::endl;
			graphicsComp->draw(mainRenderer, entityLoc.x, entityLoc.y);
			//std::cout << "finished drawing an entity" << std::endl;
		}else{
			//std::cout << "Error obtaining component" << std::endl;
		}
		//Location entityLoc = entity->getComponent<StaticLocationComponent>()->getLocation();
		//entity->getComponent<StaticGraphicsComponent>()->draw(mainRenderer, entityLoc.x, entityLoc.y);
	}
	
	SDL_RenderPresent(mainRenderer);
	
	return;
}