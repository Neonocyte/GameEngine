#include "../include/location_components.h"

void StaticLocationComponent::setLocation(int newX, int newY){
	x = newX;
	y = newY;
	
	return;
}

Location StaticLocationComponent::getLocation(){
	Location output;
	
	output.x = x;
	output.y = y;
	
	return output;	
}