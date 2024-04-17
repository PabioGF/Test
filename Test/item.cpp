#include <iostream>
#include <string>  
#include <conio.h>
#include "item.h"
#include "entity.h"
#include "player.h"

using namespace std;

Item::Item(const std::string& name, const std::string& description, Entity* owner) : Entity(name, description), owner(owner) {
	type = ITEM;
}

Entity* Item::GetOwner() {
	return owner;
}

void Item::ChangeOwner(Entity* newOwner) {
	owner = newOwner;
}

bool Item::SelectAction(Entity* play, int verb, Item* secondSelectedItem) {
    Player* player = (Player*)play;
    Room* actualRoom = player->GetRoom();
    bool theresItem = false;
    //GET ITEM
    if (verb == 1) {
        if (GetOwner() == actualRoom) {
            ChangeOwner(player);
            std::cout << "You picked the following item: " << GetName() << " (" << GetDescription() << ")" << std::endl;
            theresItem = true;
        }
        else {

            theresItem = false;
        }
    }
    //DROP ITEMS
    else if (verb == 2) {
        if (GetOwner() == player) {
            ChangeOwner(actualRoom);
            std::cout << "You droped the following item: " << GetName() << std::endl;
            theresItem = true;
        }
        else {
            theresItem = false;
        }
    }
    //MIX ITEMS
    else if (verb == 3) {
        if (secondSelectedItem) {
            if (GetOwner() == player && secondSelectedItem->GetOwner() == player) {
                ChangeOwner(secondSelectedItem);
                std::cout << "You mixed the item: " << GetName() << " with the following item: " << secondSelectedItem->GetName() << " now the item name is " << secondSelectedItem->GetName() << std::endl;
                theresItem = true;
            }
            else {
                std::cout << "You don't have the items" << std::endl;
            }
        }
    }

    return theresItem;
}