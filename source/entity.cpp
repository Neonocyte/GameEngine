#include "../include/entity.h"

std::vector<Entity *> Entity::entityVector = {};

Entity *Entity::make_entity(EntityType entityType){
	Entity *newEntity = new Entity;
	switch(entityType){
		case EntityType::ET_Furin:
			newEntity->addComponent<StaticGraphicsComponent>("furin");
			newEntity->addComponent<StaticLocationComponent>();
			break;
			
		case EntityType::ET_Player:
			break;
		//If no known type was specified, make a generic entity
		//TODO: verify generic entity does not compromise program; build new unique Entity from components?
		case EntityType::ET_Unknown:
		default:
			break;
	}
	
	entityVector.push_back(newEntity);
	return newEntity;
}