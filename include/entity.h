#ifndef ENTITY
#define ENTITY

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "components_master.h"

enum class EntityType{
	ET_Unknown = 0,
	ET_Furin,
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
				For the key, a typeid is used, which will produce a unique key for each component type.
				The value is any unique_ptr of the Component parent class; the pointer stored is of the child class (unless a generic Component is used).
				An entity may have no more than one of each type of component, as guaranteed by the typeid.
				This allows systems to easily find all components they act upon via their typeid.
				Any arguments are then forwarded to the constructor of the component.
			*/
			
			//TODO: An array would yield better performance than a map; however, not yet an issue
			components.emplace(typeid(T), std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
			
			//The following are other potential paths to implementing the function. However, they may require updates or have caveats for their usage.
			//components.insert(std::pair<std::type_index,std::unique_ptr<Component>>(typeid(T), std::unique_ptr<T>(new T(std::forward<Args>(args)...))));
			//components[std::typeid(T)] = new T;
			//components.insert(std::make_pair(typeid(T), new T));
			
			return;
		}
		
		template<class T> 
		Component *getComponent(){
			return components[typeid(T)].get();
		}
		
	private:
		int x, y, width, height;
		std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
		//TODO: implement static list of components and method to call. Make template get method for components, to allow searches for a specific type.
};

#endif