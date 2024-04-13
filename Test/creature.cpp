#include <iostream>
#include <string>  
#include <conio.h>
#include "creature.h"
#include "entity.h"

using namespace std;

Creature::Creature(const std::string& name, const std::string& description, Room* location) : Entity(name, description), location(location) {}

Room* Creature::GetRoom() {
	return location;
}

void Creature::UpdateLocation(Room* newLocation) {
	location = newLocation;
}