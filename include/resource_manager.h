#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <iostream>
#include <string>
#include <unordered_map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

//TODO: handle renderer via a system - use get call when used in loadTexture.
//TODO: convert raw pointers to smart pointers?
class ResourceManager{	
	public:
		static SDL_Texture* loadTexture(std::string path, std::string id);
		static SDL_Texture* getTexture(std::string id);
		static void freeTexture(std::string id);
		static void freeAllTextures();
		static void setRenderer(SDL_Renderer *renderer);
		
		static void logTextureMap();
	
	private:
		static const std::string defaultImagePath, defaultImageExtension;
		static std::unordered_map<std::string, SDL_Texture*> textureMap;
		static SDL_Renderer* mainRenderer;
};



#endif