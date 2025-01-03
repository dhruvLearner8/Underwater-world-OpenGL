//
//  FishSchool.h
//
//  A module to represent a school of fish.
//

#pragma once

#include <vector>

#include "ObjLibrary/Vector3.h"

#include "Entity.h"
#include "Fish.h"

class Terrain;
class FixedEntity;


//
//  FishSchool
//
//  A class to represent a school of fish.
//
//  Class Invariant:
//    <1> m_species < Fish::SPECIES_COUNT
//
class FishSchool : public Entity
{
public:
//
//  Default Constructor
//
//  Purpose: To construct a FishSchool containing no fish.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A FishSchool is constructed at the origin,
//               containing 0 fish of species 0 in a sphere of
//               radius 1.0.
//
	FishSchool ();

//
//  Constructor
//
//  Purpose: To construct a FishSchool containing the specified
//           number of fish of the specified species.
//  Parameter(s):
//    <1> school_center: The center of the school
//    <2> school_radius: The radius of the school
//    <3> fish_count: The number of fish in the school
//    <4> fish_species: The fish species
//  Precondition(s):
//    <1> Fish::isModelsLoaded()
//    <2> school_radius > 0.0
//    <3> fish_species < Fish::SPECIES_COUNT
//  Returns: N/A
//  Side Effect: A FishSchool is constructed at position
//               school_center, containing fish_count fish of
//               species fish_species in a sphere of radius
//               school_radius.
//
	FishSchool (const ObjLibrary::Vector3& school_center,
	            double school_radius,
	            unsigned int fish_count,
	            unsigned int fish_species,
		double maximum_explore_area);

//
//  getSpecies
//
//  Purpose: To determine the species of the fish in this
//           FishSchool.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The fish species.  This value will always be
//           strictly less than Fish::SPECIES_COUNT.
//  Side Effect: N/A
//
	unsigned int getSpecies () const;

//
//  getCount
//
//  Purpose: To determine the number of fish in this FishSchool.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The number of fish.
//  Side Effect: N/A
//
	unsigned int getCount () const;

//
//  draw
//
//  Purpose: To display the fish in this FishSchool.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: All fish in this FishSchool are displayed.
//
	void draw () const;

//
//  drawAllCoordinateSystems
//
//  Purpose: To display the local coordinate system for each
//           fish in this FishSchool.
//  Parameter(s):
//    <1> length: The length of the coordinate system axes
//  Precondition(s):
//    <1> length > 0.0
//  Returns: N/A
//  Side Effect: The local coordinate system for each fish in
//               this FishSchool are displayed.  Each axis has
//               length length.
//
	void drawAllCoordinateSystems (double length) const;

//
//  drawAllCollisionSpheres
//
//  Purpose: To display the collision sphere for each fish in
//           this FishSchool.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The collision sphere for each fish in this
//               FishSchool is displayed.
//
	void drawAllCollisionSpheres () const;

//
//  moveAllByVelocity
//
//  Purpose: To move all the fish in this FishSchool according
//           to their velocities.
//  Parameter(s):
//    <1> delta_time: The duration to move for
//  Precondition(s):
//    <1> delta_time >= 0.0
//  Returns: N/A
//  Side Effect: The position of each fish in this FishSchool is
//               updated for moving at its current velocity for
//               a duration of delta_time.
//
	void moveAllByVelocity (float delta_time);

//
//  applyGravityAll
//
//  Purpose: To apply gravity to all the fish in this FishSchool
//           that are currently above water.
//  Parameter(s):
//    <1> delta_time: The duration to apply gravity for
//  Precondition(s):
//    <1> delta_time >= 0.0
//  Returns: N/A
//  Side Effect: Each fish in this FishSchool is checked against
//               the surface of the water.  If it above, gravity
//               is applied.
//
	void applyGravityAll (float delta_time);

//
//  bounceAllInwards
//
//  Purpose: To make all the fish in this FishSchool bounce off
//           the inside of this FishSchool's bounding sphere.
//  Parameter(s):
//    <1> delta_time: The duration to move for
//  Precondition(s):
//    <1> delta_time >= 0.0
//  Returns: N/A
//  Side Effect: Each fish in this FishSchool is checked against
//               the school's bounding sphere.  If a fish is
//               outside the bounding sphere, it is bounced to
//               face inwards.
//
	void bounceAllInwards ();

//
//  checkCollisionAll
//
//  Purpose: To handle collisions between all fish in this
//           FishSchool and the specified Terrain.
//            Heirarchical collision checking is NOT used.
//  Parameter(s):
//    <1> terrain: The Terrain to check for collisions
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: Each fish in this FishSchool is checked for a
//               collision with terrain.  Each fish that
//               collides with terrain bounces off it.
//
	void checkCollisionAll (const Terrain& terrain);

//
//  checkCollisionAll
//
//  Purpose: To handle collisions between all fish in this
//           FishSchool and the specified FixedEntity.
//  Parameter(s):
//    <1> entity: The FixedEntity to check for collisions
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: This FishSchool is checked for a collision with
//               entity.  If there is one, each fish in this
//               FishSchool is also checked for a collision.
//               Each fish that collides with entity bounces off
//               it.
//
	void checkCollisionAll (const FixedEntity& entity);

//
//  checkPlayerCaughtFish
//
//  Purpose: To handle the player catching fish in this
//           FishSchool.
//  Parameter(s):
//    <1> player: The player Entity
//  Precondition(s): N/A
//  Returns: The number of fish caught.
//  Side Effect: This FishSchool is checked for a collision with
//               player.  If there is one, each fish in this
//               FishSchool is also checked for a collision.
//               Each fish that collides with player is removed.
//
	unsigned int checkPlayerCaughtFish (const Entity& player);

//
//  updateOrientationAll
//
//  Purpose: To adjust the orientation for all fish so they look
//           like they are swimming in the direction they are
//           moving.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The orientation of each fish in this FishSchool
//               is recalculated.
//
	void updateOrientationAll ();


	Fish& getFish(unsigned int index);

	ObjLibrary::Vector3 explore_area_center;
	double maximum_explore_distance;

	Entity flock_leader;
	ObjLibrary::Vector3 current_explore_target; 

	void AIUpdateFlockLeader(float delta_time);
	void drawLine();

	void calculateNearestNeighbour();

	ObjLibrary::DisplayList m_line_list;

	void drawLinesToNeighbour();
	void updateFishAI();
	unsigned int counter;
	ObjLibrary::Vector3 getDesiredVelocityForFish(unsigned int i);

	void AIUpdateForFish(float delta_time, unsigned int i);

	void AIUpdateFishSchool(float delta_time);

	ObjLibrary::Vector3 calculateSeperationForce(unsigned int fishIndex, unsigned int neighbourIndex);

	ObjLibrary ::Vector3 addSeperationForce(unsigned int fishIndex);

	void changeBoundingSphere();

private:
//
//  isInvariantTrue
//
//  Purpose: To determine if the class invariant is true.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether the class invariant is true.
//  Side Effect: N/A
//
	bool isInvariantTrue () const;
	
	

private:
	unsigned int m_species;
	std::vector<Fish> mv_fish;
};




