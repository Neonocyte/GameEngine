#ifndef SYSTEM
#define SYSTEM

#include "entity.h"
#include "component.h"

class System{
	/*
		Systems are the classes that update the related components on
		each entity and ask them to update.
	*/
	
	public:
		virtual void update() {};
		
	private:
};

#endif