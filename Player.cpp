

#include <cassert>
#include <vector>

#include "GetGlut.h"

#include "ObjLibrary/Vector3.h"

#include "Player.h"
#include "Collision.h"
#include "Fish.h"

using namespace std;
using namespace ObjLibrary;



Player::Player()
    : Entity(), isAutoPilot(false) {
    max_speed = 5.0;
    max_accleration = 3.0;
    }

// Parameterized constructor
Player::Player(const Vector3 & position, float radius)
    : Entity(position, radius), isAutoPilot(false) {

    max_speed = 5.0;
    max_accleration = 3.0;
    current_autoPilot_state = 1;

}


void Player::turnOnAutoPilot() {
   
    isAutoPilot = true;
}

void Player::turnOffAutoPilot() {
    isAutoPilot = false;
}

bool Player::getAutoPilotValue() {
    return isAutoPilot;
}


void Player::AI_Update(Fish& fish, float delta_time) {

    Vector3 fish_initial_pos = fish.getPosition();
    unsigned int fish_species = fish.getSpecies();

  
    Vector3 fish_velocity = fish.getVelocity();

    
    Vector3 destination = fish_initial_pos + fish_velocity * delta_time;
   
    Vector3 player_position = this->getPosition();

    Vector3 R = destination - player_position;

    float horizontal_distance = player_position.getDistanceXZ(destination);
    Vector3 D = R.getCopyWithNormSafe(max_speed);

    Vector3 S = D - this->getVelocity();

    S.truncate(max_accleration * delta_time);

    Vector3 newVelocity = this->getVelocity() + S;

    if (horizontal_distance < 5.0) {
      //  cout << "chasing fish"; 
      

        this->setVelocity(newVelocity);

        this->rotateToVector(S, 1.5 * delta_time);
        this->rotateToUpright(0.75 * delta_time);
        this->current_autoPilot_state = 2;
    }

    else
    {
        if ( -this->getPosition().y > 1) {
               // swim horizontal
         //   cout << "swim horizontal";
            newVelocity.y = 0;
            this->setVelocity(newVelocity);
            this->rotateToVector(S, 1.5 * delta_time);
            this->rotateToUpright(0.75 * delta_time);

            this->current_autoPilot_state = 0;

        }
        else {
            // go to the surface
         
            Vector3 player_velocity = this->getVelocity();
            player_velocity.x = 0;
            player_velocity.z = 0;
            player_velocity.y += max_accleration * delta_time;

            this->setVelocity(player_velocity);
            this->current_autoPilot_state = 1;

        }
    }


}

string Player::getPlayerState() {
    if (this->current_autoPilot_state == 0) {
        return "Swimming horizontal";
    }
    if (this->current_autoPilot_state == 1) {
        return "Swimming to surface, Up and Down";
    }
    if (this->current_autoPilot_state == 2) {
        return "Chasing a fish";
    }
}