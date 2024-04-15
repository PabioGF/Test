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

void Npc::SetLines(string lines) {
	textLines.push_back(lines);
}

string Npc::GetLines(int number) {
	return textLines[number];
}

void Npc::ShowLines() {
    std::cout << "Jimmy: ";
    for (size_t i = 0; i < textLines.size(); i++) {
        std::cout << textLines[i];
        if (i != textLines.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}


