#ifndef COMPONENT
#define COMPONENT

//TODO:could the Component class be better used by replacing it with a template? Additionally, is the factory function even necessary?
enum class ComponentType{
	CT_Unknown = 0
};

//ComponentGroup is used to identify the proper index for a component inside an entity's component array
enum ComponentGroup{
	CG_Unknown = -1,
	CG_Graphics = 0,
	CG_Location,
	CG_Max
};

class Component{
	/*
		Components compose the functionality of an Entity.
	*/
	public:
		//virtual void update();
		const static ComponentGroup group = CG_Unknown;
		
		static Component *makeComponent(ComponentType componentType);
};

#endif