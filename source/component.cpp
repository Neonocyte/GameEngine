#include "../include/component.h"

Component *Component::makeComponent(ComponentType componentType){
	switch(componentType){
		
		//Components define behavior, and therefore should not introduce behavior if not explicitly defined.
		case ComponentType::CT_Unknown:
		default:
			return nullptr;
	}
}