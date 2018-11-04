#ifndef PHYSICSCOMPONENT
#define PHYSICSCOMPONENT

#include "SDL2/SDL.h"

#include "component.h"

struct Velocity{
	int dx = 0;
	int dy = 0;
};

class PhysicsComponent : public Component{
	public:
		//PhysicsComponent will store the sum of forces on an object. Forces will be added to the LocationComponent after all forces have been added to the PhysicsComponent.
		
		const static ComponentGroup group = CG_Physics;
		
		PhysicsComponent();
		void addVelocity(int vx, int vy);
		virtual void clearVelocity();
		Velocity getVelocity();
		
	protected:
		int dx = 0, dy = 0;
};

class BasicPhysicsComponent : public PhysicsComponent{
	
};

class ConstantPhysicsComponent : public PhysicsComponent{
	//ConstantPhysicsComponent always has a force applied to it that is not reset at the end of each step.
	public:
		ConstantPhysicsComponent(int vx, int vy);
		void setConstantForce(int vx, int vy);
		void clearVelocity() override;
	
	private:
		int cvx = 0, cvy = 0;
};



#endif