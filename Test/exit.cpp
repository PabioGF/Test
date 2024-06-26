#include <iostream>
#include <string>  
#include <conio.h>
#include <vector>
#include "room.h"
#include "entity.h"
#include"exit.h"

using namespace std;

/**
 * Constructs an exit object with the given name, description, source, and destination rooms.
 *
 * @param name The name of the exit
 * @param description The description of the exit
 * @param source The source room of the exit
 * @param destination The destination room of the exit
 */
Exit::Exit(const std::string& name, const std::string& description, Room* source, Room* destination) : Entity(name, description), source(source), destination(destination) {
    if (name == "north" || name == "North") {
        direction = NORTH;
    }
    else if (name == "south" || name == "South") {
        direction = SOUTH;
    }
    else if (name == "east" || name == "East") {
        direction = EAST;
    }
    else if (name == "west" || name == "West") {
        direction = WEST;
    }
    type = EXIT;
}

Exit::~Exit()
{
}

/**
 * Retrieves the source room of the exit.
 *
 * @return The source room of the exit
 */
Room* Exit::GetSource() {
    return source;
}

/**
 * Retrieves the destination room of the exit.
 *
 * @return The destination room of the exit
 */
Room* Exit::GetDestination() {
    return destination;
}

/**
 * Checks if the exit leads to the specified direction.
 *
 * @param dir The direction to check
 * @return True if the exit leads to the specified direction, otherwise false
 */
bool Exit::CheckDirection(Direction dir) {
    if (dir == direction) {
        
        return true;
    }
    else {
        
        return false;
    }
    
}

/**
 * Locks the exit.
 */
void Exit::LockExit() {
    locked = true;

}

/**
 * Unlocks the exit.
 */
void Exit::UnlockExit() {
    locked = false;

}

/**
 * Checks if the exit is locked.
 *
 * @return True if the exit is locked, otherwise false
 */
bool Exit::IsLocked() {
    return locked;

}

/**
 * Gets the exits from the specified room.
 *
 * @param actualRoom The current room
 * @return True if the game has ended, otherwise false
 */
bool Exit::GetExits(Room* actualRoom) {
    bool gameEnded = false;
    if (GetSource() == actualRoom) {
        std::cout << "  - To the " << GetName() << ", there is the " << GetDestination()->GetName() << std::endl;
    }
    else if (actualRoom->GetName() == "Bathroom") {

        gameEnded = true;
    }
    return gameEnded;
}