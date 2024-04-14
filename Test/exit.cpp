#include <iostream>
#include <string>  
#include <conio.h>
#include <vector>
#include "room.h"
#include "entity.h"
#include"exit.h"

using namespace std;


Exit::Exit(const std::string& name, const std::string& description, Room* source, Room* destination) : Entity(name, description), source(source), destination(destination) {
    if (name == "north") {
        direction = NORTH;
    }
    else if (name == "south") {
        direction = SOUTH;
    }
    else if (name == "east") {
        direction = EAST;
    }
    else if (name == "west") {
        direction = WEST;
    }
}


Room* Exit::GetSource() {
    return source;
}

Room* Exit::GetDestination() {
    return destination;
}

bool Exit::CheckDirection(Direction dir) {
    if (dir == direction) {
        
        return true;
    }
    else {
        
        return false;
    }
    
}