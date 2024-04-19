#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include "entity.h"

using namespace std;

class Room : public Entity {
public:
	//int exits[];


public:
	Room(const std::string& name, const std::string& description);
	~Room();
};

#endif // !EXIT