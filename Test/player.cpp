#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"
#include "player.h"
#include "creature.h"
#include "exit.h"

using namespace std;

Player::Player(const std::string& name, const std::string& description, Room* location): Creature(name, description, location){
	type = PLAYER;
}

bool Player::MovePlayer(Entity* entity, bool hasKey, string direction, bool& hasMoved, Room* actualRoom) {
	bool isLocked = false;

    Exit* exit = (Exit*)entity->GetEntityByType(EXIT);
    if (exit) {
        if (exit->IsLocked() && hasKey) {
            exit->UnlockExit();
        }
        if (exit->GetSource() == actualRoom) {
            //std::cout << "theresNeigbor " << exit->GetSource()->GetName() << std::endl;

            if (direction == "north") {
                if (exit->CheckDirection(NORTH)) {
                    if (!exit->IsLocked()) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
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
            if (direction == "south") {
                if (exit->CheckDirection(SOUTH)) {
                    if (!exit->IsLocked()) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
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

            if (direction == "east") {

                if (exit->CheckDirection(EAST)) {
                    if (!exit->IsLocked()) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
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

            if (direction == "west") {

                if (exit->CheckDirection(WEST)) {
                    if (!exit->IsLocked()) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
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