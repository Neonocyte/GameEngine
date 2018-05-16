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

/*
template<class T, typename ...Args> 
void Entity::addComponent(Args... args){
	/*
		The following inserts a new component into an entity's component map.
		For the key, a typeid is used, which will produce a unique key for each component type.
		The value is any unique_ptr of the Component parent class; the pointer stored is of the child class (unless a generic Component is used).
		An entity may have no more than one of each type of component, as guaranteed by the typeid.
		This allows systems to easily find all components they act upon via their typeid.
		Any arguments are then forwarded to the constructor of the component.
	*//*
	
	//TODO: An array would yield better performance than a map; however, not yet an issue
	components.emplace(typeid(T), std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
	
	//The following are other potential paths to implementing the function. However, they may require updates or have caveats for their usage.
	//components.insert(std::pair<std::type_index,std::unique_ptr<Component>>(typeid(T), std::unique_ptr<T>(new T(std::forward<Args>(args)...))));
	//components[std::typeid(T)] = new T;
	//components.insert(std::make_pair(typeid(T), new T));
	
	return;
}

template<class T> 
T *Entity::getComponent(){
	return components[typeid(T)];
}*/