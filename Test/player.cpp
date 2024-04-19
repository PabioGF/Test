#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"
#include "player.h"
#include "creature.h"
#include "exit.h"

using namespace std;

/**
 * Constructs a player object with the given name, description, and starting location.
 *
 * @param name The name of the player
 * @param description The description of the player
 * @param location The starting location of the player
 */
Player::Player(const std::string& name, const std::string& description, Room* location): Creature(name, description, location){
	type = PLAYER;
}

Player::~Player()
{
}

/**
 * Moves the player to the specified direction.
 *
 * @param entity The exit entity representing the direction to move
 * @param hasKey Indicates whether the player has the necessary key to unlock the exit
 * @param direction The direction in which the player intends to move
 * @param hasMoved A reference boolean indicating whether the player has successfully moved
 * @param actualRoom The current room of the player
 * @return True if the exit is locked, false otherwise
 */
bool Player::MovePlayer(Entity* entity, bool hasKey, string direction, bool& hasMoved, Room* actualRoom) {
	bool isLocked = false;

    Exit* exit = (Exit*)entity->GetEntityByType(EXIT);
    if (exit) {
        //If the exit is locked and the player has the key, unlock it

        if (exit->GetSource() == actualRoom) {

            //If there's an exit move player north
            if (direction == "north") {
                if (exit->CheckDirection(NORTH)) {
                    if (!exit->IsLocked() || (exit->IsLocked() && hasKey)) {
                        std::cout << "Heading to the " << exit->GetDestination()->GetName() << std::endl;
                        UpdateLocation(exit->GetDestination());
                        hasMoved = true;
                    }
                    else {
                        hasMoved = false;
                        isLocked = true;
                        std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                    }

                }



            }
            //If there's an exit move player south
            if (direction == "south") {
                if (exit->CheckDirection(SOUTH)) {
                    if (!exit->IsLocked() || (exit->IsLocked() && hasKey)) {
                        std::cout << "Heading to the " << exit->GetDestination()->GetName() << std::endl;
                        UpdateLocation(exit->GetDestination());
                        hasMoved = true;
                    }
                    else {
                        hasMoved = false;
                        isLocked = true;
                        std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                    }

                }



            }
            //If there's an exit move player east
            if (direction == "east") {

                if (exit->CheckDirection(EAST)) {
                    if (!exit->IsLocked() || (exit->IsLocked() && hasKey)) {
                        std::cout << "Heading to the " << exit->GetDestination()->GetName() << std::endl;
                       UpdateLocation(exit->GetDestination());
                       hasMoved = true;
                    }
                    else {
                        hasMoved = false;
                        isLocked = true;
                        std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                    };

                }



            }
            //If there's an exit move player west
            if (direction == "west") {

                if (exit->CheckDirection(WEST)) {
                    if (!exit->IsLocked() || (exit->IsLocked() && hasKey)) {
                        std::cout << "Heading to the " << exit->GetDestination()->GetName() << std::endl;
                        UpdateLocation(exit->GetDestination());
                        hasMoved = true;
                    }
                    else {
                        hasMoved = false;
                        isLocked = true;
                        std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                    }

                }



            }

        }

    }


	return isLocked;
}