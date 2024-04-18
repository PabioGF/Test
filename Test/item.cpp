#include <iostream>
#include <string>  
#include <conio.h>
#include "item.h"
#include "entity.h"
#include "player.h"

using namespace std;

/**
 * Constructs an Item object with the given name, description, and owner.
 *
 * @param name The name of the item
 * @param description The description of the item
 * @param owner The entity that owns the item
 */
Item::Item(const std::string& name, const std::string& description, Entity* owner) : Entity(name, description), owner(owner) {
	type = ITEM;
}


/**
 * Gets the owner of the item.
 *
 * @return A pointer to the entity that owns the item
 */
Entity* Item::GetOwner() {
	return owner;
}

/**
 * Changes the owner of the item.
 *
 * @param newOwner The new owner of the item
 */
void Item::ChangeOwner(Entity* newOwner) {
	owner = newOwner;
}

/**
 * Performs the selected action on the item.
 *
 * @param play The entity performing the action (usually the player)
 * @param verb The type of interaction verb: 1 for 'get', 2 for 'drop', 3 for 'mix'
 * @param secondSelectedItem The second item involved in the action (optional)
 * @return True if the action was successfully performed, false otherwise
 */
bool Item::SelectAction(Entity* play, int verb, Item* secondSelectedItem) {
    Player* player = (Player*)play;
    Room* actualRoom = player->GetRoom();
    bool theresItem = false;
    //GET ITEM
    if (verb == 1) {
        if (GetOwner() == actualRoom) {
            ChangeOwner(player);
            std::cout << "You picked up the following item: " << GetName() << " (" << GetDescription() << ")" << std::endl;
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
            std::cout << "You dropped the following item: " << GetName() << std::endl;
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
                std::cout << "You don't have those items." << std::endl;
            }
        }
    }

    return theresItem;
}