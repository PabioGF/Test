#include <iostream>
#include <string>  
#include <conio.h>
#include "entity.h"
#include "npc.h"
#include "creature.h"

using namespace std;

Npc::Npc(const std::string& name, const std::string& description, Room* location) : Creature(name, description, location) {
	type: NPC;
}