#pragma once
#ifndef EXIT_HPP
#define EXIT_HPP


#include "entity.h"

class Room;

enum Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

using namespace std;

class Exit : public Entity {
public:
	
	Direction direction;
	Room* source;
	Room* destination;

public:
	Exit(const std::string& name, const std::string& description, Room* source, Room* destination);
	Room* GetSource();
	Room* GetDestination();
	bool CheckDirection(Direction direction);
};


#endif // !EXIT
