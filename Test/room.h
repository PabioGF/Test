#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include "entity.h"

using namespace std;

class Room : public Entity {
public:
	//int exits[];
	string neighborNorth;
	string neighborSouth;
	string neighborEast;
	string neighborWest;

public:
	Room(const std::string& name, const std::string& description, const std::string& neighborNorth, const std::string& neighborSouth, const std::string& neighborEast, const std::string& neighborWest);
	vector<int> GetExits(Room* room);
	string GetNorthNeighbor();
	string GetSouthNeighbor();
	string GetEastNeighbor();
	string GetWestNeighbor();
	//void AddEntity(Entity* entity);


};

#endif // !EXIT