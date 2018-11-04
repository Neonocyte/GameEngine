#include <iostream>
#include <string>
#include <vector>
#include <chrono>
//#include <thread>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../include/system_master.h"
#include "../include/entity.h"
#include "../include/resource_manager.h"
#include "../include/graphics_system.h"

const int MS_PER_FRAME = 15; //16.6 MS/frame gives 60 fps

int screen_width = 640;
int screen_height = 480;
bool running = true;
std::string windowTitle = "Game Demo";
std::vector<System*> systemsVector;

SDL_Window* mainWindow = nullptr;
SDL_Event e;

bool init();
bool initTests();
void processInput();
void close();
void logError(std::string error);

int main(int argv, char** args){
	
	if(init()){
		while(running){
			auto start = std::chrono::high_resolution_clock::now();
			
			processInput();
			
			for(System* curSystem : systemsVector){
				//std::cout << "in loop" << std::endl;
				curSystem->update();
			}
			
			//TODO: research consistent delay times. The thread library requires MinGW to use POSIX threads, and both SDL_Delay() and sleep_for() may have inconsistent timing. If this becomes a problem, a custom delay may be required.
			//Make each loop last the same amount of time by adding a delay.
			auto end = std::chrono::high_resolution_clock::now();
			
			//TODO: This compiles, but is highly suspect. Is loopDuration correct?
			std::chrono::duration<float> loopDuration = end - start; //duration is measured in seconds
			
			//Delay only if loop is ahead of target MS_PER_FRAME
			int delay = MS_PER_FRAME - (loopDuration.count() * 100);
			if(delay > 0){
				SDL_Delay(MS_PER_FRAME - (loopDuration.count() * 100));
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds((double)MS_PER_FRAME - loopDuration));
		}
		
		close();
	}

	return 0;
}

bool init(){
	bool initSuccess = true;
	
	//Initialize SDL, exiting if failed
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		logError("SDL could not initialize. SDL_Error: " + std::string(SDL_GetError()));
		initSuccess = false;
	}else{
		mainWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if(mainWindow == nullptr){
			logError("SDL could not create a window. SDL_Error: " + std::string(SDL_GetError()));
			initSuccess = false;
		}else{
			systemsVector.push_back(new MovementSystem());
			systemsVector.push_back(new GraphicsSystem(mainWindow));
			
			//TODO: make test run on compile flag
			if(!initTests()){
				logError("Tests could not initialize.");
				initSuccess = false;
			}
		}
	}
	
	return initSuccess;
}

bool initTests(){
	//Code to initialize tests. Not to be run in final build.
	bool initSuccess = true;
	
	
	//Create a series of entities with locations for testing purposes. ET_Furin is a basic entity type only used for test purposes.
	Entity *testEntity = NULL;
	LocationComponent *staticLocationComp;
	
	if(staticLocationComp = static_cast<LocationComponent*>(Entity::make_entity(EntityType::ET_Furin)->getComponent(CG_Location))){
		staticLocationComp->setLocation(15,15);
	}else{
		logError("Could not set new entity location during testing");
	}
	
	if(staticLocationComp = static_cast<LocationComponent*>(Entity::make_entity(EntityType::ET_Furin)->getComponent(CG_Location))){
		staticLocationComp->setLocation(80,15);
	}else{
		logError("Could not set new entity location during testing");
	}
	
	if(staticLocationComp = static_cast<LocationComponent*>(Entity::make_entity(EntityType::ET_Furin)->getComponent(CG_Location))){
		staticLocationComp->setLocation(110,15);
	}else{
		logError("Could not set new entity location during testing");
	}
	
	if(staticLocationComp = static_cast<LocationComponent*>(Entity::make_entity(EntityType::ET_Furin)->getComponent(CG_Location))){
		staticLocationComp->setLocation(150,15);
	}else{
		logError("Could not set new entity location during testing");
	}
	
	
	//Create entity for physics test
	if((testEntity = Entity::make_entity(EntityType::ET_Furin)) == NULL){
		logError("Could not create new test entity");
	}else{
		if(staticLocationComp = static_cast<LocationComponent*>(testEntity->getComponent(CG_Location))){
			staticLocationComp->setLocation(50,50);
			testEntity->addComponent<ConstantPhysicsComponent>(3,3);
			if(!(testEntity->getComponent(CG_Physics))){
				logError("Could not add ConstantPhysicsComponent to an entity during testing");
			}
		}else{
			logError("Could not set new entity location during testing");
		}
	}
	
	return initSuccess;
}

void processInput(){
	//TODO: Properly store input for Components to reference - move to a system.
	//TODO: allow the quit event to end the program without completing another cycle.
	//processInput should be used to gather input from the machine, but should only be used to escape from the game in case of a Control system error.
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_QUIT){
			running = false;
		}
	}
}

void close(){
	//TODO: free loaded textures
	
	SDL_DestroyWindow(mainWindow);
	
	SDL_Quit();
	
	return;
}

void logError(std::string error){//Stub
	//TODO: Should probably print to a file.
	//TODO: Move error logging to its own cpp file
	//TODO: Implement proper logging in graphics_system.cpp
	std::cout << error << std::endl;
}