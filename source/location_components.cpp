#include "../include/location_components.h"

void LocationComponent::setLocation(int newX, int newY){
	x = newX;
	y = newY;
	
	return;
}

Location LocationComponent::getLocation(){
	Location output;
	
	output.x = x;
	output.y = y;
	
	return output;	
}

void LocationComponent::translate(int incX, int incY){
	x += incX;
	y += incY;
	
	return;
}