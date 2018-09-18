#ifndef GRAPHICSCOMPONENT
#define GRAPHICSCOMPONENT

#include <string>

#include "SDL2/SDL.h"

#include "component.h"
#include "resource_manager.h"

class GraphicsComponent : public Component{
	public:
		//StaticGraphicsComponent(std::string imageID, int x, int y, int width, int height);
		//void update() override;
		
		const static ComponentGroup group = CG_Graphics;
		
		void draw(SDL_Renderer *renderer, int x, int y);
		void setImage(std::string imageID);
		void setSubimage(int x, int y, int width, int height);
	private:
		//TODO: replace subimage dimensions with SDL_Rect?
		int subimageX = 0, subimageY = 0, subimageWidth, subimageHeight;
		SDL_Texture *imageTexture;
};

class StaticGraphicsComponent : public GraphicsComponent{
	public:
		StaticGraphicsComponent();
		StaticGraphicsComponent(std::string imageID);

};

#endif