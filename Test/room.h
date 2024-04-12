#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP


#include "entity.h"

using namespace std;

class Room : public Entity {
public:
	Room(const std::string& name, const std::string& description);


	//void AddEntity(Entity* entity);


};

#endif // !EXIT