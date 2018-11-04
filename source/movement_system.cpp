#include "../include/movement_system.h"


MovementSystem::MovementSystem(){
	
}

MovementSystem::~MovementSystem(){
	
}

void MovementSystem::update(){
	for(auto entity : Entity::entityVector){
		LocationComponent *locationComp;
		PhysicsComponent *physicsComp;
		
		if((locationComp = static_cast<LocationComponent*>(entity->getComponent(CG_Location))) && (physicsComp = static_cast<PhysicsComponent*>(entity->getComponent(CG_Physics)))){
			Velocity entityVelocity = physicsComp->getVelocity();
			locationComp->translate(entityVelocity.dx, entityVelocity.dy);
			physicsComp->clearVelocity();
		}
	}
	return;
}