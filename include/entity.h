#ifndef ENTITY
#define ENTITY

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "components_master.h"

enum class EntityType{
	//The following entity types are used to prevent and handle potential errors.
	ET_Unknown = 0,
	
	//The following entity types are only for testing purposes
	ET_Furin,
	
	//The following entity types are for use in game.
	ET_Player
};

class Entity{
	/*
		Entities are generic in-game objects comprised of Components.
		These Components control most aspects of an Entity's behavior.
		The defined Entities are commonly used Entities included for the sake of convenience.
	*/
	
	public:
		~Entity();
		static Entity *make_entity(EntityType entityType);
		static std::vector<Entity *> entityVector;
		
		template<class T, typename ...Args> 
		void addComponent(Args... args){
			/*
				The following inserts a new component into an entity's component map.
				For the key, a a ComponentGroup constant is used, which will ensure a unique key for each component type.
				The value is any unique_ptr of the component's group type (generally, the parent); the pointer stored is of the child class (unless a generic Component is used).
				An entity may have no more than one of each type of component.
				This allows systems to easily find all components they act upon via their ComponentGroup.
				Any arguments are then forwarded to the constructor of the component.
			*/
			
			//SOLVED?: TODO: An array would yield better performance than a map; however, not yet an issue
			//TODO: Remove the following previous methods used to handle components once the current method is sufficiently tested.
			//components.emplace(typeid(T), std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
			//The following are other potential paths to implementing the function. However, they may require updates or have caveats for their usage.
			//components.insert(std::pair<std::type_index,std::unique_ptr<Component>>(typeid(T), std::unique_ptr<T>(new T(std::forward<Args>(args)...))));
			//components[std::typeid(T)] = new T;
			//components.insert(std::make_pair(typeid(T), new T));
			components[T::group] = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
			
			
			
			return;
		}
		
		Component *getComponent(ComponentGroup cg){
			return components[cg].get();
		}
		
	private:
		int x, y, width, height;
		
		//Previous revisions used a map to store components, rather than an array.
		//std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
		std::unique_ptr<Component> components[ComponentGroup::CG_Max] = {};
};

#endif