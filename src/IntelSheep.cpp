#include "IntelSheep.h"

IntelSheep::IntelSheep(const SpatialVector& pos, const SpatialVector& vel) : Thing(pos, vel) {
//~ IntelSheep::IntelSheep(const SpatialVector& pos, const SpatialVector& vel, World* world) : Thing(pos, vel, world) {
	
	m_speed					= 1.0;
	m_friction				= 0.0;
	m_mass					= 100.0;
	m_eatingRange			= 10.0;
	m_perceptionRange		= 50.0;
	m_healthConsumption		= 0.1;
	m_health				= 100.0;
	
	classID					= "IntelSheep";
	
}

void IntelSheep::perceive(World* world) {
	
	thingsInSight = world->getThings(m_position, m_perceptionRange, m_velocity, M_PI_4);
	
	
}

void IntelSheep::progress(double dt, World* world) {
	
	perceive(world);
	
	// ANA: add AI processing here!
	
	move(dt);
	
	std::list<Thing*> thingsInFront = world->getThings(m_position, m_eatingRange, m_velocity, M_PI_4);
	
	
	for(std::list<Thing*>::iterator it = thingsInFront.begin(); it != thingsInFront.end(); ++it) {
		
		// eat the berries!
		if ((*it)->getClassID() == "Berry") {
			m_health += (*it)->giveUpHealth(this);
		}
		
	}
	
}

void IntelSheep::move(double dt) {
	
	m_velocity.normalize(m_speed);	// ANA: intelsheep has a constant speed
									// ANA: velocity direction shall be generated by NN
									
	Thing::move(dt);
	
	
	if(m_health > 1.0) 	
		m_health -= m_healthConsumption * dt;
	
	
	
	
}