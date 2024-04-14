#include <iostream>
#include <string>  
#include <conio.h>
#include <vector>
#include "room.h"
#include "entity.h"

using namespace std;

Room::Room(const std::string& name, const std::string& description, const std::string& north, const std::string& south, const std::string& east, const std::string& west) : Entity(name, description), neighborNorth(north), neighborSouth(south), neighborEast(east), neighborWest(west) {
	type: ROOM;
}

vector<int> Room:: GetExits(Room* actualRoom){
	vector<int> exits;




	return exits;
}


string Room::GetNorthNeighbor() {

	return neighborNorth;
}
string Room::GetSouthNeighbor() {

	return neighborSouth;
}
string Room::GetEastNeighbor() {

	return neighborEast;
}
string Room::GetWestNeighbor() {

	return neighborWest;
}