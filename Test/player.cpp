#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"
#include "player.h"
#include "creature.h"

using namespace std;

Player::Player(const std::string& name, const std::string& description, Room* location): Creature(name, description, location){}
