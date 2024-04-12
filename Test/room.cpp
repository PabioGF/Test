#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"

using namespace std;

Room::Room(const std::string& name, const std::string& description) : Entity(name, description) {}