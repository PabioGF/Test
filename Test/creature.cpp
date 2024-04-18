#include <iostream>
#include <string>  
#include <conio.h>
#include "creature.h"
#include "entity.h"

using namespace std;

/**
 * Constructs a creature object with the given name, description, and location.
 *
 * @param name The name of the creature
 * @param description The description of the creature
 * @param location The location of the creature
 */
Creature::Creature(const std::string& name, const std::string& description, Room* location) : Entity(name, description), location(location) {
	type = CREATURE;
}

/**
 * Retrieves the room where the creature is located.
 *
 * @return The room where the creature is located
 */
Room* Creature::GetRoom() {
	return location;
}

/**
 * Updates the location of the creature.
 *
 * @param newLocation The new location of the creature
 */
void Creature::UpdateLocation(Room* newLocation) {
	location = newLocation;
}