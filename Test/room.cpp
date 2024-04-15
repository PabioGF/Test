#include <iostream>
#include <string>  
#include <conio.h>
#include <vector>
#include "room.h"
#include "entity.h"

using namespace std;

Room::Room(const std::string& name, const std::string& description) : Entity(name, description) {
	type: ROOM;
}

vector<int> Room:: GetExits(Room* actualRoom){
	vector<int> exits;




	return exits;
}

