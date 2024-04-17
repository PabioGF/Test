#include <iostream>
#include <string>  
#include <conio.h>
#include "entity.h"
#include "npc.h"
#include "creature.h"
#include "player.h"
#include "item.h"

using namespace std;

Npc::Npc(const std::string& name, const std::string& description, Room* location) : Creature(name, description, location) {
	type = NPC;
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


bool Npc::SelectAction(Creature* play, int verb, Entity* itemNpc, Entity* itemSelected) {
    bool npcKilled = false;
    Player* player = (Player*)play;
    Item* npcItem = (Item*)itemNpc;
    Item* selectedItem = (Item*)itemSelected;
    Room* actualRoom = player->GetRoom();
    if (player) {
        if (player->GetRoom() == GetRoom()) {
            if (verb == 1) {
                ShowLines();
                std::cout << "Your thoughts: Wow, this is endless, bring him the damn egg pasta dish or kill him alredy." << std::endl;
            }
            if (verb == 2) {
                //Kill jimmy
                if (npcItem) {
                    npcItem->ChangeOwner(actualRoom);
                    std::cout << "The following itemwas droped: " << npcItem->GetName() << std::endl;
                }

                npcKilled = true;

                std::cout << "Your thoughts: Omg, i wasn't serious, ok..." << std::endl;
            }
            if (verb == 3) {
                if (selectedItem) {
                    if (selectedItem->GetOwner() == player) {
                        selectedItem->ChangeOwner(this);
                        std::cout << "You gave " << selectedItem->GetName() << " to " << GetName() << std::endl;
                        std::cout << GetName() << ": Wow, thanks! here you have: " << std::endl;
                        if (npcItem) {
                            npcItem->ChangeOwner(player);
                            std::cout << GetName() << " gave you " << npcItem->GetName() << std::endl;
                        }
                    }
                    else {
                        std::cout << "you don't have this item" << std::endl;
                    }
                }
                else {
                    std::cout << "you don't have this item" << std::endl;
                }
            }
        }
        else {
            std::cout << GetName() << " is not here." << std::endl;
        }
    }

    return npcKilled;
}




