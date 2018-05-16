#include "../include/resource_manager.h"

const std::string ResourceManager::defaultImagePath = "./images/";
const std::string ResourceManager::defaultImageExtension = ".png";
std::unordered_map<std::string, SDL_Texture*> ResourceManager::textureMap {};
SDL_Renderer* ResourceManager::mainRenderer = nullptr;

SDL_Texture* ResourceManager::loadTexture(std::string path, std::string id){
	
	//Prevent duplicates in texture map
	if(textureMap.find(id) != textureMap.end()){
		return textureMap.at(id);
	}
	
	SDL_Texture* optimizedTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //can be replaced with BMP_Load if using .bmp file
	
	if(loadedSurface == nullptr){
		//TODO: add proper logging
		std::cout << "Unable to load image " << path << ". SDL_image Error: " << IMG_GetError() << std::endl;
		//logError("Unable to load image " + path + ". SDL_image Error: " + std::string(IMG_GetError()));
	}else{
		optimizedTexture = SDL_CreateTextureFromSurface(mainRenderer, loadedSurface);
		if(optimizedTexture == nullptr){
			//TODO: add proper logging
			std::cout << "Unable to optimize image " << path << ". SDL Error: " << SDL_GetError() << std::endl;
			//logError("Unable to create texture from " + path + ". SDL Error: " + std::string(SDL_GetError()));
		}else{
			//textureMap.insert(std::pair<std::string,SDL_Texture*>(id, optimizedTexture));
			textureMap.emplace(id, optimizedTexture);
		}
		SDL_FreeSurface(loadedSurface);
	}
	
	return optimizedTexture;
}

SDL_Texture* ResourceManager::getTexture(std::string id){
	if(textureMap.find(id) == textureMap.end()){
		//TODO: add proper logging
		//TODO: possibly attempt to load missing texture?
		//return nullptr;
		return loadTexture(defaultImagePath + id + defaultImageExtension, id);
	}else{
		return textureMap.at(id);
	}
}

void ResourceManager::freeTexture(std::string id){
	//TODO: either implement smart pointers with a deleter, or manually delete each texture to avoid memory leaks.
	if(textureMap.erase(id)){
		//TODO: add proper logging
	}else{
		//TODO: add proper logging
		std::cout << "Unable to locate texture to free." << std::endl;
	}
	
	return;
}

void ResourceManager::freeAllTextures(){
	//TODO: either implement smart pointers with a deleter, or manually delete each texture to avoid memory leaks.
	textureMap.clear();
	
	return;
}

void ResourceManager::setRenderer(SDL_Renderer *renderer){
	ResourceManager::mainRenderer = renderer;
	
	return;
}

void ResourceManager::logTextureMap(){
	//TODO: add proper logging
	
	std::unordered_map<std::string, SDL_Texture*>::iterator textureIterator = textureMap.begin();
	
	while(textureIterator != textureMap.end()){
		std::cout << textureIterator->first << " :: " << textureIterator->second << std::endl;
		++textureIterator;
	}
	
	
	return;
}