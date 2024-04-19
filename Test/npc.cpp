#include <iostream>
#include <string>  
#include <conio.h>
#include "entity.h"
#include "npc.h"
#include "creature.h"
#include "player.h"
#include "item.h"

using namespace std;

/**
 * Constructs an NPC object with the given name, description, and location.
 *
 * @param name The name of the NPC
 * @param description The description of the NPC
 * @param location The room where the NPC is located
 */
Npc::Npc(const std::string& name, const std::string& description, Room* location) : Creature(name, description, location) {
	type = NPC;
}

Npc::~Npc()
{
}

/**
 * Sets the lines of dialogue for the NPC.
 *
 * @param lines The lines of dialogue to be set
 */
void Npc::SetLines(string lines) {
	textLines.push_back(lines);
}

/**
 * Displays all the lines of dialogue for the NPC.
 */
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

/**
 * Performs the selected action on the NPC.
 *
 * @param play The creature performing the action (usually the player)
 * @param verb The type of interaction verb: 1 for 'talk', 2 for 'kill', 3 for 'give'
 * @param itemNpc The item related to the NPC (optional)
 * @param itemSelected The item selected by the player (optional)
 * @return True if the NPC was killed during the action, false otherwise
 */
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
                std::cout << "Your thoughts: Wow, this is endless, either I give him the damn pasta with egg or I'll kill him." << std::endl;
            }
            if (verb == 2) {
                //Kill jimmy
                if (npcItem) {
                    npcItem->ChangeOwner(actualRoom);
                    std::cout << "The following item was dropped: " << npcItem->GetName() << std::endl;
                }

                npcKilled = true;

                std::cout << "Your thoughts: OMG, I wasn't serious, ok..." << std::endl;
            }
            if (verb == 3) {
                if (selectedItem) {
                    if (selectedItem->GetOwner() == player) {
                        selectedItem->ChangeOwner(this);
                        std::cout << "You gave " << selectedItem->GetName() << " to " << GetName() << std::endl;
                        std::cout << GetName() << ": Wow, thanks! Here you go " << std::endl;
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




