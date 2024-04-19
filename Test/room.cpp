#include <iostream>
#include <string>  
#include <conio.h>
#include <vector>
#include "room.h"
#include "entity.h"

using namespace std;

/**
 * Constructs a room object with the given name and description.
 *
 * @param name The name of the room
 * @param description The description of the room
 */
Room::Room(const std::string& name, const std::string& description) : Entity(name, description) {
	type = ROOM;
}

Room::~Room()
{
}
