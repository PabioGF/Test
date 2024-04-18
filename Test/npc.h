#pragma once
#ifndef NPC_HPP
#define NPC_HPP
#endif

#include "creature.h"
#include <list>
#include <string>

using namespace std;

class Npc : public Creature {
public:
	Npc(const std::string& name, const std::string& description, Room* location);
	void SetLines(string line);
	void ShowLines();
	bool SelectAction(Creature* player, int verb, Entity* npcItem, Entity* selectedItem);

public:
	vector<string> textLines;
	
};