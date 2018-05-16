#ifndef COMPONENT
#define COMPONENT

//TODO:could the Component class be better used by replacing it with a template? Additionally, is the factory function even necessary?
enum class ComponentType{
	CT_Unknown = 0
};

class Component{
	/*
		Components compose the functionality of an Entity.
	*/
	public:
		//virtual void update();
		static Component *makeComponent(ComponentType componentType);
};

#endif