
#pragma once

#include "ObjLibrary/Vector3.h"
#include "ObjLibrary/DisplayList.h"

#include "CoordinateSystem.h"

#include "Entity.h"
#include "Fish.h"

using namespace ObjLibrary;
using namespace std;


//
//  Entity
//
//  A class to store an entity on the map.  An Entity has a
//    local coordinate system and a radius.
//
//  Class Invariant:
//    <1> m_radius >= 0.0
//
class Player : public Entity {
    
public:
   
   /* Player(const ObjLibrary::Vector3& center,
        double radius);*/
   
    bool isAutoPilot = false;

    Player();
       

    // Parameterized constructor
    Player(const Vector3& position, float radius);

    void turnOnAutoPilot();
    void turnOffAutoPilot();
    bool getAutoPilotValue();
       
    void AI_Update(Fish& fish,float delta_time);
    string getPlayerState();
    // Other player-specific methods...

     unsigned  int fishSchoolIndex;
     unsigned int fishIndex;
     double max_speed;
     double max_accleration;
     unsigned int current_autoPilot_state;

    private:
};