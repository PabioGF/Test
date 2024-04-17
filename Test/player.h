#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#endif

#include "creature.h"
#include "room.h"
#include <list>
#include <string>

using namespace std;

class Player : public Creature {
public:
	Player(const std::string& name, const std::string& description, Room* location);
	bool MovePlayer(Entity* entity, bool hasKey, string direction, bool& hasMoved, Room* room);
};