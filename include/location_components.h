#ifndef LOCATIONCOMPONENT
#define LOCATIONCOMPONENT

#include "component.h"

//TODO: research and more properly decide on a way to store and transfer coordinates.
//All done via struct? No struct, return via tuple? Store a struct or individual coordinates?
struct Location{
	int x = 0;
	int y = 0;
};

class LocationComponent : public Component{
	public:
		//void update() override;
		Location getLocation();
		
		const static ComponentGroup group = CG_Location;
		
		void setLocation(int newX, int newY);
	private:
		int x = 0, y = 0;
};

class StaticLocationComponent : public LocationComponent{
	
};

#endif