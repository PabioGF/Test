#pragma once
#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "entity.h"
#include "room.h"
#include <list>
#include <string>

using namespace std;

using namespace std;

class Room;

class Creature: public Entity {
public:
	Creature(const std::string& name, const std::string& description, Room* location);
	Room* GetRoom();
	void UpdateLocation(Room* location);
private:
	Room* location;
};



#endif // !EXIT
