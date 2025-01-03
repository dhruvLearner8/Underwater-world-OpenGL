//
//  FishSchool.cpp
//

#include "FishSchool.h"

#include <cassert>
#include <vector>

#include "GetGlut.h"

#include "ObjLibrary/Vector3.h"

#include "Entity.h"
#include "Fish.h"
#include "Terrain.h"
#include "FixedEntity.h"
#include "Collision.h"

using namespace std;
using namespace ObjLibrary;



FishSchool :: FishSchool ()
		: Entity(Vector3::ZERO, 1.0),
		  m_species(0)
		// mv_fish will be initialized to empty by the default constructor
{
	assert(isInvariantTrue());
	explore_area_center = Vector3(0.0,0.0,0.0);
	maximum_explore_distance = 1.0;
	flock_leader.setPosition(Vector3(0.0, 0.0, 0.0));
	current_explore_target = Vector3(0.0, 0.0, 0.0);
	counter = (rand() % (60 - 0)) + 0;
	
	
}

FishSchool :: FishSchool (const ObjLibrary::Vector3& school_center,
                          double school_radius,
                          unsigned int fish_count,
                          unsigned int fish_species, double maximum_explore_area)
		: Entity(school_center, school_radius),
		  m_species(fish_species)
		// mv_fish will be initialized below
{
	assert(Fish::isModelsLoaded());
	assert(school_radius > 0.0);
	assert(fish_species < Fish::SPECIES_COUNT);

	explore_area_center = school_center;
	maximum_explore_distance = maximum_explore_area;

	flock_leader.setPosition(school_center);
	current_explore_target = school_center;

	

	double speed = Fish::getSpeed(fish_species);

	for(unsigned int i = 0; i < fish_count; i++)
	{
		Vector3 position = school_center + Vector3::getRandomSphereVector() * school_radius;
		Vector3 forward  = Vector3::getRandomUnitVector();
		Fish fish(position, forward, fish_species);
		fish.setVelocity(forward * speed);
		mv_fish.push_back(fish);
	}


	
	assert(mv_fish.size() == fish_count);

	assert(isInvariantTrue());
}



unsigned int FishSchool :: getSpecies () const
{
	assert(isInvariantTrue());

	return m_species;
}

unsigned int FishSchool :: getCount () const
{
	assert(isInvariantTrue());

	return mv_fish.size();
}

void FishSchool :: draw () const
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < mv_fish.size(); i++)
		mv_fish[i].draw();
}

void FishSchool :: drawAllCoordinateSystems (double length) const
{
	assert(isInvariantTrue());
	assert(length > 0.0);

	for(unsigned int i = 0; i < mv_fish.size(); i++)
	{
		glPushMatrix();
			mv_fish[i].applyDrawTransformations();
			glBegin(GL_LINES);
				glColor3d(1.0, 0.0, 0.0);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(length, 0.0, 0.0);
				glColor3d(0.0, 1.0, 0.0);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(0.0, length, 0.0);
				glColor3d(0.0, 0.0, 1.0);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(0.0, 0.0, length);
			glEnd();
		glPopMatrix();
	}
}

void FishSchool :: drawAllCollisionSpheres () const
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < mv_fish.size(); i++)
	{
		double radius = mv_fish[i].getRadius();
		glPushMatrix();
			mv_fish[i].applyDrawTransformations();
			glScaled(radius, radius, radius);
			glutWireIcosahedron();
			//glutWireSphere(1.0, 8, 6);
		glPopMatrix();
	}
}



void FishSchool :: moveAllByVelocity (float delta_time)
{
	assert(isInvariantTrue());
	assert(delta_time >= 0.0);

	for(unsigned int i = 0; i < mv_fish.size(); i++)
		mv_fish[i].moveByVelocity(delta_time);

	flock_leader.moveByVelocity(delta_time);
	//drawLine();

	assert(isInvariantTrue());
}

void FishSchool :: applyGravityAll (float delta_time)
{
	assert(isInvariantTrue());
	assert(delta_time >= 0.0);

	for(unsigned int i = 0; i < mv_fish.size(); i++)
		if(mv_fish[i].getPosition().y > 0)
			mv_fish[i].applyGravity(delta_time);

	assert(isInvariantTrue());
}

void FishSchool :: bounceAllInwards ()
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < mv_fish.size(); i++)
	{
		Vector3 fish_pos = mv_fish[i].getPosition();
		if(fish_pos.isDistanceGreaterThan(getPosition(), getRadius()))
		{
			Vector3 normal = getPosition() - fish_pos;
			normal.normalize();
			mv_fish[i].bounce(normal);
		}
	}

	assert(isInvariantTrue());
}

void FishSchool :: checkCollisionAll (const Terrain& terrain)
{
	assert(isInvariantTrue());

	// no school-level check

	for(unsigned int i = 0; i < mv_fish.size(); i++)
		if(isCollision(mv_fish[i], terrain))
		{
			Vector3 surface_normal = terrain.getSurfaceNormal(mv_fish[i].getPosition());
			mv_fish[i].bounce(surface_normal);
		}

	assert(isInvariantTrue());
}

void FishSchool :: checkCollisionAll (const FixedEntity& entity)
{
	assert(isInvariantTrue());

	if(isCollision(*this, entity))
	{
		for(unsigned int i = 0; i < mv_fish.size(); i++)
		{
			Fish& r_fish = mv_fish[i];
			if(isCollision(entity, r_fish))
			{
				Vector3 surface_normal = entity.getSurfaceNormal(r_fish.getPosition());
				r_fish.bounce(surface_normal);
			}
		}
	}

	assert(isInvariantTrue());
}

unsigned int FishSchool :: checkPlayerCaughtFish (const Entity& player)
{
	assert(isInvariantTrue());

	unsigned int caught_count = 0;
	if(isCollision(*this, player))
	{
		for(unsigned int i = 0; i < mv_fish.size(); i++)
			if(isCollision(player, mv_fish[i]))
			{
				caught_count++;

				// remove fish from vector
				mv_fish[i] = mv_fish.back();
				mv_fish.pop_back();
				i--;  // don't skip new fish in this spot


			}
	}

	assert(isInvariantTrue());
	return caught_count;
}

void FishSchool :: updateOrientationAll ()
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < mv_fish.size(); i++)
		mv_fish[i].setOrientation(mv_fish[i].getVelocity().getNormalized());

	assert(isInvariantTrue());
}



bool FishSchool :: isInvariantTrue () const
{
	if(m_species >= Fish::SPECIES_COUNT)
		return false;
	return true;
}


Fish& FishSchool::getFish(unsigned int index)
{
	return mv_fish[index];
}

void FishSchool::AIUpdateFlockLeader(float delta_time) {

	Vector3 leaderPosition = flock_leader.getPosition();

	// If leader position near to explore target, choose a new and seek that 
	unsigned int m_species = this->getSpecies();
	double max_speed = Fish::getSpeed(m_species);
	double max_accleration = Fish::getMaxAccleration(m_species) * 0.70;

	double newDistance = Fish::getSpeed(m_species) * delta_time;

	float horizontal_distance = leaderPosition.getDistanceXZ(current_explore_target);

	if (horizontal_distance < newDistance) {
	
		// get a new target make a function to do that and update current target
		Vector3 chosen = this->getPosition() + Vector3::getRandomSphereVector() * this->getRadius();

		this->current_explore_target = chosen;

		//cout << "this is player position :" << flock_leader.getPosition() << " this is current explore target :" << current_explore_target;
		

	}

	//seek(current_explore_target);
	
	Vector3 R = current_explore_target - leaderPosition;

	Vector3 D = R.getCopyWithNormSafe(max_speed * 0.85);

	Vector3 S = D - flock_leader.getVelocity();

	S.truncate(max_accleration *delta_time * 0.70);

	Vector3 newVelocity = flock_leader.getVelocity() + S;

	flock_leader.setVelocity(newVelocity);

	AIUpdateFishSchool(delta_time);
	

}




void FishSchool::drawLine()
{
	//cout << "called";
	Vector3 leaderPosition = flock_leader.getPosition();
	Vector3 current_explore_target = this->current_explore_target;
	//cout << "this is leader position  :" << leaderPosition << " this is currentn explore target :" << this->current_explore_target;
	
	glColor3d(1.0, 0.0, 0.0);
	glPushMatrix();
	glBegin(GL_LINES);
	
	glVertex3d(leaderPosition.x,leaderPosition.y,leaderPosition.z);
	glVertex3d(current_explore_target.x,current_explore_target.y,current_explore_target.z);
	
	glEnd();
	glPopMatrix();

	glColor3d(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(leaderPosition.x, leaderPosition.y, leaderPosition.z);
	glutWireSphere(0.1, 10, 10);
	glEnd();
	glPopMatrix();

	glColor3d(1.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(current_explore_target.x, current_explore_target.y, current_explore_target.z);
	glutWireSphere(0.1, 10, 10);
	glEnd();
	glPopMatrix();

}


void FishSchool::calculateNearestNeighbour() {
	
	if (mv_fish.size() == 0) {
		return;
	}

	
	unsigned int fishSchoolSize = this->getCount();
	
	double tempArray[4];
	unsigned int neighbourArray[4];

	for (int i = 0; i < 4; i++) {
		tempArray[i] = 1000.0;
		neighbourArray[i] = 0;
	}

	

	for (int i = counter; i < fishSchoolSize; i+=60) {

		Vector3 fishPosition = mv_fish[i].getPosition();

		for (int k = 0; k < fishSchoolSize; k++) {
			if (k == i) {
				continue;
			}
			else {
				Vector3 fishPosition2 = mv_fish[k].getPosition();

				double distance = fishPosition.getDistanceXY(fishPosition2);

				for (int j = 0; j < 4; j++) {

					if (distance < tempArray[j]) {
						tempArray[j] = distance;
						neighbourArray[j] = k;
						
						break;
					}
				}
			}
			
		}

		for (int j = 0; j < 4; j++) {
			mv_fish[i].fishNeighbour[j] = neighbourArray[j];
		}

		
	}
	counter++;
	if (counter >= 60) {
		counter = 0;
	}

}

void FishSchool::drawLinesToNeighbour() {

	if (this->getCount() == 0) {
		return;
	}

	unsigned int fishIndex = 0;

	
	Vector3 fishPosition1 = mv_fish[0].getPosition();
	
	for (int i = 0; i < 4; i++) {
		
		unsigned int fish2Index = mv_fish[0].fishNeighbour[i];
		if (fish2Index  < this->getCount())
		{
			
			Vector3 fishPosition2 = mv_fish[fish2Index].getPosition();
			/*cout << "fish index 2: " << fish2Index;*/
			//cout << "this is pos1 :" << fishPosition1 << " this is pos 2: " << fishPosition2;
			glColor3d(0.0, 0.0, 0.0);
			glPushMatrix();
			glBegin(GL_LINES);

			glVertex3d(fishPosition1.x, fishPosition1.y, fishPosition1.z);
			glVertex3d(fishPosition2.x, fishPosition2.y, fishPosition2.z);

			glEnd();
			glPopMatrix();

		}


		glColor3d(0.0, 1.0, 1.0);
		glPushMatrix();
		glBegin(GL_LINES);

		glVertex3d(fishPosition1.x, fishPosition1.y, fishPosition1.z);
		glVertex3d(flock_leader.getPosition().x,flock_leader.getPosition().y,flock_leader.getPosition().z);

		glEnd();
		glPopMatrix(); 
		}
		

}


Vector3 FishSchool::getDesiredVelocityForFish(unsigned int i) {

	Vector3 leaderPosition = flock_leader.getPosition();

	
	unsigned int m_species = this->getSpecies();
	double max_speed = Fish::getSpeed(m_species);

	Vector3 R =  leaderPosition - mv_fish[i].getPosition();

	Vector3 D = R.getTruncated(max_speed);
	return D;
}

void FishSchool::AIUpdateForFish(float delta_time, unsigned int i) {

	unsigned int m_species = this->getSpecies();
	double max_acc = Fish::getMaxAccleration(m_species);
	double max_speed = Fish::getSpeed(m_species);

	Vector3 steering_force = addSeperationForce(i);

	Vector3 D = getDesiredVelocityForFish(i) + (3.0 * steering_force);
	D.truncate(max_speed);

	Vector3 S = D - mv_fish[i].getVelocity();

	S.truncate(max_acc * delta_time);

	Vector3 newVelocity = mv_fish[i].getVelocity() + S ;


	mv_fish[i].setVelocity(newVelocity);

	changeBoundingSphere();

}

void FishSchool::AIUpdateFishSchool(float delta_time) {

	for (int i = 0; i < mv_fish.size(); i++) {

		AIUpdateForFish(delta_time, i);

	}

}


Vector3 FishSchool :: calculateSeperationForce(unsigned int fishIndex, unsigned int neighbourIndex) {

	unsigned int m_species = this->getSpecies();
	double max_speed = Fish::getSpeed(m_species);
	
	Vector3 fishPosition1 = mv_fish[fishIndex].getPosition();
	Vector3 fishPosition2 = mv_fish[neighbourIndex].getPosition();

	double distance = fishPosition1.getDistance(fishPosition2);

	
	double maximum_seperation_distance = mv_fish[fishIndex].getRadius() * 4.0;

	if (distance > maximum_explore_distance) {
		Vector3 seperation_force (0.0, 0.0, 0.0);
		return seperation_force;
	}

	Vector3 difference = fishPosition1 - fishPosition2;
	difference.getNormalizedSafe();

	double closeness = 1.0 - (distance / maximum_seperation_distance);

	double magnitude = closeness * closeness * max_speed;

	return (difference * magnitude); // seperation force
}

Vector3 FishSchool::addSeperationForce(unsigned int fishIndex) {

	Vector3 seperationForce(0.0, 0.0, 0.0);

	for (int i = 0; i < 4; i++) {
		unsigned int neighbourIndex = mv_fish[fishIndex].fishNeighbour[i];
		if (neighbourIndex < this->getCount()) {
			
			Vector3 tempSeperationForce = calculateSeperationForce(fishIndex, neighbourIndex);

			seperationForce += tempSeperationForce;
		}

	}

	//cout << seperationForce;

	return seperationForce;
}


void FishSchool::changeBoundingSphere()
{
	Vector3 position(0.0, 0.0, 0.0);

	for (int i = 0; i < mv_fish.size(); i++) {
		Vector3 fishPosition = mv_fish[i].getPosition();

		position += fishPosition;
	}

	position = position / mv_fish.size();
	this->setPosition(position);
	
	double max_distance = 0;

	for (int i = 0; i < mv_fish.size(); i++) {
		double distance = position.getDistance(mv_fish[i].getPosition());

		if (distance > max_distance) {
			max_distance = distance;
		}
	}

	this->setRadius(max_distance);
}