#include "../include/graphics_components.h"

StaticGraphicsComponent::StaticGraphicsComponent(std::string imageID){
	setImage(imageID);
}

void GraphicsComponent::setImage(std::string imageID){
	imageTexture = ResourceManager::getTexture(imageID);
	
	//Reset subimage to include the entire texture
	subimageX = 0;
	subimageY = 0;
	SDL_QueryTexture(imageTexture, NULL, NULL, &subimageWidth, &subimageHeight);
	
	return;
}

void GraphicsComponent::setSubimage(int x, int y, int width, int height){
	subimageX = x;
	subimageY = y;
	subimageWidth = width;
	subimageHeight = height;
	
	return;
}

void GraphicsComponent::draw(SDL_Renderer *renderer, int x, int y){
	SDL_Rect srcrect, dstrect;
	
	//std::cout << "Graphics Component draw start" << std::endl;
	
	srcrect.x = subimageX;
	srcrect.y = subimageY;
	srcrect.w = subimageWidth;
	srcrect.h = subimageHeight;
	
	//std::cout << "SDL_Rect constructed" << std::endl;
	
	//dstrect uses the same width and height as the subimage to prevent shrinking/stretching; transforms could be handled by another function
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = subimageWidth;
	dstrect.h = subimageHeight;
	
	//std::cout << "SDL_Rect constructed" << std::endl;
	std::cout << "Texture " << imageTexture << std::endl;
	
	
	SDL_RenderCopy(renderer, imageTexture, &srcrect, &dstrect);
	
	return;
}