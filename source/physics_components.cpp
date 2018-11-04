#include "../include/physics_components.h"

PhysicsComponent::PhysicsComponent(){
	
}

void PhysicsComponent::addVelocity(int vx, int vy){
	dx += vx;
	dy += vy;
	
	return;
}

void PhysicsComponent::clearVelocity(){
	//Clear forces in preparation for the next step. Use sparingly elsewhere.
	dx = 0;
	dy = 0;
	
	return;
}

Velocity PhysicsComponent::getVelocity(){
	Velocity output;
	
	output.dx = dx;
	output.dy = dy;
	
	return output;	
}

ConstantPhysicsComponent::ConstantPhysicsComponent(int vx, int vy){
	cvx = vx;
	cvy = vy;
}

void ConstantPhysicsComponent::setConstantForce(int vx, int vy){
	cvx = vx;
	cvy = vy;
	
	return;
}

void ConstantPhysicsComponent::clearVelocity(){
	dx = cvx;
	dy = cvy;
	
	return;
}