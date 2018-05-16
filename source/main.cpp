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
//SDL_Surface* mainSurface = NULL;
//TODO: Remove testTexture
//SDL_Texture* testTexture = nullptr;
SDL_Event e;

bool init();
void processInput();
//void draw();
//SDL_Renderer* mainRenderer = nullptr;
//SDL_Texture* loadTexture(std::string path);
void close();
void logError(std::string error);

int main(int argv, char** args){
	
	if(init()){
		//TODO: remove testTexture and its loop
		//testTexture = loadTexture("./images/furin.png");
		//if(testTexture != nullptr){
			while(running){
				auto start = std::chrono::high_resolution_clock::now();
				
				processInput();
				//draw();
				
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
		//}
		
		close();
	}

	return 0;
}

bool init(){
	bool initSuccess = true;
	
	//Initialize SDL, exiting if failed
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		//std::cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << std::endl;
		logError("SDL could not initialize. SDL_Error: " + std::string(SDL_GetError()));
		initSuccess = false;
	}else{
		mainWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if(mainWindow == nullptr){
			//std::cout << "SDL could not create a window. SDL_Error: " << SDL_GetError() << std::endl;
			logError("SDL could not create a window. SDL_Error: " + std::string(SDL_GetError()));
			initSuccess = false;
		}else{
			systemsVector.push_back(new GraphicsSystem(mainWindow));
			
			//TODO: remove temporary entity creation in following lines
			StaticLocationComponent *staticLocationComp;
			
			if(staticLocationComp = static_cast<StaticLocationComponent*>(Entity::make_entity(EntityType::ET_Furin)->getComponent<StaticLocationComponent>())){
				staticLocationComp->setLocation(15,15);
			}
			
			//std::cout << "Init finished." << std::endl;
			
			/*
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if(mainRenderer == nullptr){
				logError("Renderer could not initialize. SDL Error: " + std::string(SDL_GetError()));
				initSuccess = false;
			}else{
				SDL_SetRenderDrawColor(mainRenderer, 0xF5, 0xE3, 0xAD, 0xFF);
				
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					//std::cout << "SDL_image could not initialize. SDL_image Error: " << IMG_GetError() << std::endl;
					logError("SDL_image could not initialize. SDL_image Error: " + std::string(IMG_GetError()));
					initSuccess = false;
				}
			}*/
		}
	}
	
	return initSuccess;
}

void processInput(){
	//TODO: Properly store input for Components to reference - move to a system.
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_QUIT){
			running = false;
		}
	}
}

/*
void draw(){	
	//TODO: Remove following temp code - move drawing to appropriate systems
	//Following SDL_Rect is to prevent stretching while rendering testTexture
	SDL_Rect dstrect;
	
	dstrect.x = 20;
	dstrect.y = 0;
	dstrect.w = 25 * 2;
	dstrect.h = 77 * 2;
	
	SDL_RenderClear(mainRenderer);
	SDL_RenderCopy(mainRenderer, testTexture, nullptr, &dstrect);
	SDL_RenderPresent(mainRenderer);
	
}
*/

/*
SDL_Texture* loadTexture(std::string path){
	SDL_Texture* optimizedTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //can be replaced with BMP_Load if using .bmp file
	
	if(loadedSurface == nullptr){
		//std::cout << "Unable to load image " << path << ". SDL_image Error: " << IMG_GetError() << std::endl;
		logError("Unable to load image " + path + ". SDL_image Error: " + std::string(IMG_GetError()));
	}else{
		optimizedTexture = SDL_CreateTextureFromSurface(mainRenderer, loadedSurface);
		if(optimizedTexture == nullptr){
			//std::cout << "Unable to optimize image " << path << ". SDL Error: " << SDL_GetError() << std::endl;
			logError("Unable to create texture from " + path + ". SDL Error: " + std::string(SDL_GetError()));
		}
		SDL_FreeSurface(loadedSurface);
	}
	
	return optimizedTexture;
}
*/

void close(){
	//TODO: free loaded textures
	
	//TODO: remove this cleanup after properly implementing graphics.
	//SDL_DestroyTexture(testTexture);
	
	//SDL_DestroyRenderer(mainRenderer);
	
	SDL_DestroyWindow(mainWindow);
	
	SDL_Quit();
	
	return;
}

void logError(std::string error){//Stub
	//TODO: Should probably print to a file.
	std::cout << error << std::endl;
}