#include <iostream>
#include <string>  
#include <conio.h>
#include "world.h"
#include "room.h"
#include "creature.h"
#include "player.h"
#include "npc.h"
#include "item.h"
#include "exit.h"

using namespace std;

// Constructor for the World class
World::World() {
    // Initialize rooms
    Room* startingRoom = new Room("Entrance Hall", "You are in the Entrance hall, there's nothing here to see.");
    Room* kitchen = new Room("Kitchen", "Here you can cook you som eggs and pasta that someone left on the fride, unless you are alergic to pasta, or eggs...");
    Room* livingRoom = new Room("Living Room", "Here is the heart of the house, wit conection with the entrance hall, the bathroom and Jimmy's bedroom.");
    Room* bedroom = new Room("Bedroom", "Here is Jimmy lying in his bed, hes very bored, he wishes he could talk to somebody.");
    Room* bathroom = new Room("Bathroom", "A normal bathroom");

    // Initialize player
    Player* player = new Player("You", "You are very handsome, and most important, you need to go to the bathroom.", startingRoom);

    // Initialize NPCs
    Npc* jimmy = new Npc("Jimmy", "He talks a lot, don't talk to him unless is absolutly necessary.", bedroom);
    jimmy->SetLines("Hey, I didn't see you, thank goodness you're here because I'm dying of boredom and I needed to talk to someone, how are you?");
    jimmy->SetLines(" Me not very well, the truth the other day my girlfriend and i broke up and it has made me think a lot about life and about what I'm going to do with it.");
    jimmy->SetLines(" The only thing that always cheers me up is a good egg pasta dish but only Jessica knew how to make it, even is only mix egg an pasta, by the way I have started to invest in NFT, what do you think? ");
    jimmy->SetLines(" I think I'm going to get rich in the future, and then you'll see how Jessica comes back,");
    jimmy->SetLines(" speaking of her, the last day we met she was wearing some nike sneakers from the flea market that looked really cool, I think I should talk to her again,");
    jimmy->SetLines(" you know, just to ask him about the shoes, nothing else, wow, talking so much makes you very hungry, don't you think so too? ");
    jimmy->SetLines(" What? You need to get in the bathroom? I have the key! Wow, that remembbers me of when... ");

    // Initialize items
    Item* egg = new Item("Egg", "An egg, hopes nothing alive inside.", kitchen);
    Item* pasta = new Item("Pasta", "Pasta, you know ho loved pasta? I don't.", kitchen);
    Item* key = new Item("Key", "Key of the door in the bathroom", jimmy);

    // Initialize exits
    Exit* exit1 = new Exit("south", "path to kitchen", startingRoom, kitchen);
    Exit* exit2 = new Exit("north", "path to entrance", kitchen, startingRoom);
    Exit* exit3 = new Exit("east", "path to living room", startingRoom, livingRoom);
    Exit* exit4 = new Exit("west", "path to entrance", livingRoom, startingRoom);
    Exit* exit5 = new Exit("east", "path to bedroom", livingRoom, bedroom);
    Exit* exit6 = new Exit("west", "path to living room", bedroom, livingRoom);
    Exit* exit7 = new Exit("north", "path living room and bathroom", livingRoom, bathroom);
    exit7->LockExit();

    // Push entities to the world entities vector
    entities.push_back(player);
    entities.push_back(startingRoom);
    entities.push_back(kitchen);
    entities.push_back(livingRoom);
    entities.push_back(bedroom);
    entities.push_back(bathroom);
    entities.push_back(jimmy);
    entities.push_back(egg);
    entities.push_back(pasta);
    entities.push_back(key);
    entities.push_back(exit1);
    entities.push_back(exit2);
    entities.push_back(exit3);
    entities.push_back(exit4);
    entities.push_back(exit5);
    entities.push_back(exit6);
    entities.push_back(exit7);
}

// Destructor for the World class
World::~World() {
    // Deallocate memory for all entities
    for (Entity* entity : entities) {
        delete entity;
    }
}


/**
* Handles directional input from the user
*
* @param inputLower The input string from the user, converted to lowercase
* @return True if the input is not recognized, false otherwise
*/

bool World::InputDirection(string inputLower) {
    bool noRecognize = false;
    int direction = 0;
    string dir;
    size_t northPos = inputLower.find("north");
    size_t southPos = inputLower.find("south");
    size_t eastPos = inputLower.find("east");
    size_t westPos = inputLower.find("west");

    //Check north
    if (northPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (northPos == 0) ? ' ' : inputLower[northPos - 1];
        char charAfter = (northPos + 5 >= inputLower.size()) ? ' ' : inputLower[northPos + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectDirectionVerb(inputLower);
            if (!noRecognize) {
                direction = 1;
                dir = "north";
            }
        }
        else {

            noRecognize = true;
        }
    }
    //Check south
    else if (southPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (southPos == 0) ? ' ' : inputLower[southPos - 1];
        char charAfter = (southPos + 5 >= inputLower.size()) ? ' ' : inputLower[southPos + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectDirectionVerb(inputLower);
            if (!noRecognize) {
                direction = 2;
                dir = "south";
            }
        }
        else {
            noRecognize = true;
        }
    }
    //Check east
    else if (eastPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (eastPos == 0) ? ' ' : inputLower[eastPos - 1];
        char charAfter = (eastPos + 4 >= inputLower.size()) ? ' ' : inputLower[eastPos + 4];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectDirectionVerb(inputLower);
            if (!noRecognize) {
                direction = 3;
                dir = "east";
            }
        }
        else {
            noRecognize = true;
        }
    }
    //check west
    else if (westPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (westPos == 0) ? ' ' : inputLower[westPos - 1];
        char charAfter = (westPos + 4 >= inputLower.size()) ? ' ' : inputLower[westPos + 4];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectDirectionVerb(inputLower);
            if (!noRecognize) {
                direction = 4;
                dir = "west";
            }
        }
        else {
            noRecognize = true;
        }
    }
    else if (inputLower.find("quit") != std::string::npos) {
        std::cout << "Saliendo del juego!" << std::endl;
    }
    else {
        noRecognize = true;
    }
    if (direction != 0) {
        LookRooms(dir);
    }
    return noRecognize;
}

/**
* Handles item-related input from the user
*
* @param inputLower The input string from the user, converted to lowercase
* @return True if the input is not recognized, false otherwise
*/
bool World::InputItem(string inputLower) {
    bool noRecognize = false;
    size_t egg = inputLower.find("egg");
    size_t pasta = inputLower.find("pasta");
    size_t key = inputLower.find("key");
    string item = "";
    int verb = 0;
    string secondItem = "";

    //check egg
    if (egg != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (egg == 0) ? ' ' : inputLower[egg - 1];
        char charAfter = (egg + 4 >= inputLower.size()) ? ' ' : inputLower[egg + 4];
        if (!std::isalpha(charBefore)) {// && !std::isalpha(charAfter)) {
            verb = DetectItemVerb(inputLower);
            if (verb != 0) {
                noRecognize = false;
                item = "Egg";
            }
        }
        else {

            noRecognize = true;
        }
    }
    //check pasta
    else if (pasta != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (pasta == 0) ? ' ' : inputLower[pasta - 1];
        char charAfter = (pasta + 5 >= inputLower.size()) ? ' ' : inputLower[pasta + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            verb = DetectItemVerb(inputLower);
            if (verb != 0) {
                noRecognize = false;
                item = "Pasta";
            }
        }
        else {
            noRecognize = true;
        }
    }
    //check key
    else if (key != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (key == 0) ? ' ' : inputLower[key - 1];
        char charAfter = (key + 3 >= inputLower.size()) ? ' ' : inputLower[key + 3];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            verb = DetectItemVerb(inputLower);
            if (verb != 0) {
                noRecognize = false;
                item = "Key";
            }
        }
        else {
            noRecognize = true;
        }
    }
    //check egg and pasta at the same time
    if (egg != std::string::npos && pasta != std::string::npos) {
        char charBeforeEgg = (egg == 0) ? ' ' : inputLower[egg - 1];
        char charAfterEgg = (egg + 3 >= inputLower.size()) ? ' ' : inputLower[egg + 3];
        char charBeforePasta = (pasta == 0) ? ' ' : inputLower[pasta - 1];
        char charAfterPasta = (pasta + 5 >= inputLower.size()) ? ' ' : inputLower[pasta + 5];
        if (!std::isalpha(charBeforeEgg) && !std::isalpha(charAfterEgg) && !std::isalpha(charBeforePasta) && !std::isalpha(charAfterPasta)) {
            verb = DetectItemVerb(inputLower);
            if (verb != 0) {
                noRecognize = false;
                item = "Egg";
                secondItem = "Pasta";

            }
        }
        else {
            noRecognize = true;
        }
    }

    if (!LookItems(item, secondItem, verb) && verb != 0) {
        std::cout << "That item is not here" << std::endl;
    }

    item = "";
    return noRecognize;
}


/**
* Handles NPC-related input from the user
*
* @param inputLower The input string from the user, converted to lowercase
* @return True if the input is not recognized, false otherwise
*/
bool World::InputNpc(string inputLower) {
    bool noRecognize = false;
    int npcVerb = 0;
    size_t jimmy = inputLower.find("jimmy");
    size_t pasta = inputLower.find("pasta");
    string item = "";
    string npcName = "";
    //check for jimmy
    if (jimmy != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (jimmy == 0) ? ' ' : inputLower[jimmy - 1];
        char charAfter = (jimmy + 5 >= inputLower.size()) ? ' ' : inputLower[jimmy + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            npcVerb = DetectNpcVerb(inputLower);
            if (npcVerb != 0) {
                npcName = "Jimmy";
                noRecognize = false;
            }
        }
        else {
            noRecognize = true;
        }
    }
    //check for jimmy and pasta at the same time
    if (jimmy != std::string::npos && pasta != std::string::npos) {
        char charBeforeJim = (jimmy == 0) ? ' ' : inputLower[jimmy - 1];
        char charAfterJim = (jimmy + 5 >= inputLower.size()) ? ' ' : inputLower[jimmy + 5];
        char charBeforePasta = (pasta == 0) ? ' ' : inputLower[pasta - 1];
        char charAfterPasta = (pasta + 5 >= inputLower.size()) ? ' ' : inputLower[pasta + 5];
        if (!std::isalpha(charBeforeJim) && !std::isalpha(charAfterJim) && !std::isalpha(charBeforePasta) && !std::isalpha(charAfterPasta)) {
            npcVerb = DetectNpcVerb(inputLower);
            if (npcVerb != 0) {
                npcName = "Jimmy";
                item = "Pasta";
                noRecognize = false;

            }
        }
        else {
            noRecognize = true;
        }
    }

    if (npcVerb != 0) {
        InteractNpcs(npcName, item, npcVerb);
    }

    if (noRecognize) {
        std::cout << "Comando no reconocido." << std::endl;
    }
    return noRecognize;
}

/**
* Processes the user input and performs appropriate actions
*
* @param input The input string from the user
*/
void World::ProcessInput(string input) {
    string inputLower = input;

    bool noRecognize = true;
    for (char& character : inputLower) {
        character = std::tolower(character);
    }

    //CHECK DIRECTIONS

    noRecognize = InputDirection(inputLower);

    //CHECK ITEMS

    noRecognize = InputItem(inputLower);

    //NPC INTERACIONS
    
    noRecognize = InputNpc(inputLower);



}


/**
* Starts the game world, initializing player and displaying initial information
*/
void World::Start() {
    //Get the player
    Player* player = nullptr;
    for (Entity* entity : entities) {
        player = (Player*)entity->GetEntityByType(PLAYER);
        break;

    } 
    //Display the information
    if (player) {
        std::cout << player->GetName() << ": " << player->GetDescription() << std::endl;
    }
    else {
        std::cout << "No se ha encontrado el jugador en el mundo." << std::endl;
    }
    
    RoomDescription();
}

/**
* Displays the exits of the current room and checks for game-ending conditions
*/
void World::RoomDescription() {
    //Get the player
    Player* player = nullptr;
    for (Entity* entity : entities) {
        player = (Player*)entity->GetEntityByType(PLAYER);
        break;

    }
    if (player) {
        Room* actualRoom = player->GetRoom();
        vector<string> neighbor;
        string direction;
        bool gameEnded = false;
        //Get exits
        for (Entity* entity : entities) {
            Exit* exit = (Exit*)entity->GetEntityByType(EXIT);
            if (exit) {
                gameEnded = exit->GetExits(actualRoom);
            }
        }
        if (gameEnded) {
            std::cout << "Ha acabado el juego!" << std::endl;
            exit(0);
        }
    }

}

/**
 * Checks the current room for items and NPCs and displays them
 */
void World::RoomContainsSomething() {
    //Get player
    Player* player = nullptr;
    for (Entity* entity : entities) {
        player = (Player*)entity->GetEntityByType(PLAYER);
        break;

    }
    if (player) {
        //Get the actual room and check if owns something or someoene
        Room* actualRoom = player->GetRoom();

        for (Entity* entity : entities) {
            Item* item = (Item*)entity->GetEntityByType(ITEM);
            Npc* npc = (Npc*)entity->GetEntityByType(NPC);
            if (item) {
                if (item->GetOwner() == actualRoom) {
                    std::cout << "There's an item in this room: " << item->GetName() << std::endl;

                }
            }
            if (npc) {
                if (npc->GetRoom() == actualRoom) {
                    std::cout << "There's someone in this room: " << npc->GetName() << " (" << npc->GetDescription() << ")" << std::endl;

                }
            }
        }
    }

}

/**
 * Checks if there are neighboring rooms in the specified direction and moves the player if possible
 *
 * @param direction The direction in which to look for neighboring rooms
 * @return True if there are neighboring rooms, false otherwise
 */
bool World::LookRooms(string direction) {
    bool theresNeigbor = false;
    Player* player = nullptr;
    //Get player
    for (Entity* entity : entities) {
        player = (Player*)entity->GetEntityByType(PLAYER);
        break;

    }
    if (player) {
        Room* actualRoom = player->GetRoom();
        string neighbor;
        int cont = 0;
       
        bool isLocked = false;
        bool hasKey = false;
        bool hasMoved = false;

        //We search for the item Key and we look if the player owns it
        for (Entity* entity : entities) {
            Item* item = (Item*)entity->GetEntityByTypeName(ITEM, "Key");
            if (item) {
                if (item->GetOwner() == player) {
                    hasKey = true;
                }

            }

        }

        //We look for the exits and moove the player to the selected one
        for (Entity* entity : entities) {
            isLocked = player->MovePlayer(entity, hasKey, direction, hasMoved, actualRoom);
            if (hasMoved) {
                RoomDescription();
                RoomContainsSomething();
                hasMoved = false;
            }
        }
        if (player->GetRoom() == actualRoom && !isLocked) {
            std::cout << "There's nothing in that direction " << std::endl;
        }
    }

    return theresNeigbor;
}


/**
 * Interacts with NPCs based on the provided NPC name
 *
 * @param npcName The name of the NPC to interact with
 * @param itemName The name of the item involved in the interaction
 * @param verb The type of interaction verb
 */
void World::InteractNpcs(string npcName, string itemName, int verb) {
    Player* player = nullptr;
    Npc* selectedNpc = nullptr;
    Item* selectedItem = nullptr;
    Item* npcItem = nullptr;
    bool detected = false;
    bool npcKilled = false;
    //Get player
    for (Entity* entity : entities) {
        player = (Player*)entity->GetEntityByType(PLAYER);
        break;

    }
    if (player) {
        
        //Get npc
        for (Entity* entity : entities) {

            Npc* npc = (Npc*)entity->GetEntityByTypeName(NPC, npcName);

            if (npc) {
                selectedNpc = npc;
            }

        }

        if (selectedNpc) {
            for (Entity* entity : entities) {
                //We look if the the pasta oowns the egg, for knowing if is mixed
                Item* item = (Item*)entity->GetEntityByType(ITEM);
                if (item) {
                    if (item->GetOwner()->GetName() == itemName) {
                        selectedItem = (Item*)item->GetOwner()->GetEntityByType(ITEM);

                    }
                    if (item->GetOwner()->GetName() == selectedNpc->GetName()) {
                        npcItem = item;
                    }

                }
            }


            npcKilled = selectedNpc->SelectAction(player, verb, npcItem, selectedItem);

            //if the player was killed we eliminate it
            if (npcKilled) {

                for (auto it = entities.begin(); it != entities.end(); ++it) {
                    Npc* npc = (Npc*)(*it)->GetEntityByType(NPC);
                    if (npc && npc == selectedNpc) {
                        delete* it;
                        entities.erase(it);
                        break;
                    }
                }
            }
        }
    }

}


/**
 * Looks for items in the player's current room and performs actions on them based on the provided item names and verb
 *
 * @param itemName The name of the first item involved in the interaction
 * @param secondItem The name of the second item involved in the interaction
 * @param verb The type of interaction verb
 * @return True if there are items present, false otherwise
 */
bool World::LookItems(string itemName, string secondItem ,int verb) {
    
    Item* selectedItem = nullptr;
    Item* secondSelectedItem = nullptr;
    Player* player = nullptr;
    bool theresItem = true;
    //Get player
    for (Entity* entity : entities) {
        player = (Player*)entity->GetEntityByType(PLAYER);
        break;

    }
    if (player) {
        //Get the item
        for (Entity* entity : entities) {
            Item* item = (Item*)entity->GetEntityByType(ITEM);
            if (item) {
                if (item->GetName() == itemName) {
                    selectedItem = item;

                }
                if (item->GetName() == secondItem) {
                    secondSelectedItem = item;
                }

            }

        }

        //Perform the selected action 
        if (selectedItem) {
            theresItem = selectedItem->SelectAction(player, verb, secondSelectedItem);
        }

    }
    
    return theresItem;
}

/**
 * Detects if the input string contains a direction-related verb
 *
 * @param inputLower The input string in lowercase
 * @return True if a direction-related verb is detected, false otherwise
 */
bool World::DetectDirectionVerb(string inputLower) {
    bool noRecognize = true;

    size_t goPos = inputLower.find("go");
    if (goPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (goPos + 3 >= inputLower.size()) ? ' ' : inputLower[goPos + 3];
        if (std::isalpha(charAfter)) {
            noRecognize = false;
            
        }
        else {
            noRecognize = true;
        }
    }



    return noRecognize;

}

/**
 * Detects the type of interaction verb related to items in the input string
 *
 * @param inputLower The input string in lowercase
 * @return The type of interaction verb: 0 for no recognized verb, 1 for 'get' or 'pick', 2 for 'drop', 3 for 'mix' or 'put'
 */
int World::DetectItemVerb(string inputLower) {
    int verb = 0;

    //GET ITEMS
    size_t getPos = inputLower.find("get");
    if (getPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (getPos + 4 >= inputLower.size()) ? ' ' : inputLower[getPos + 4];
        if (std::isalpha(charAfter)) {
            verb = 1;

        }
        else {
            verb = 0;
        }
    }

    size_t pickPos = inputLower.find("pick");
    if (pickPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (pickPos + 5 >= inputLower.size()) ? ' ' : inputLower[pickPos + 5];
        if (std::isalpha(charAfter)) {
            verb = 1;

        }
        else {
            verb = 0;
        }
    }

    //DROP ITEMS
    size_t dropPos = inputLower.find("drop");
    if (dropPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (dropPos + 5 >= inputLower.size()) ? ' ' : inputLower[dropPos + 5];
        if (std::isalpha(charAfter)) {
            verb = 2;

        }
        else {
            verb = 0;
        }
    }

    //MIX ITEMS

    size_t mixPos = inputLower.find("mix");
    if (mixPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (mixPos + 4 >= inputLower.size()) ? ' ' : inputLower[mixPos + 4];
        if (std::isalpha(charAfter)) {
            verb = 3;

        }
        else {
            verb = 0;
        }
    }

    size_t putPos = inputLower.find("put");
    if (putPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (putPos + 4 >= inputLower.size()) ? ' ' : inputLower[putPos + 4];
        if (std::isalpha(charAfter)) {
            verb = 3;

        }
        else {
            verb = 0;
        }
    }



    return verb;

}

/**
 * Detects the type of interaction verb related to NPCs in the input string
 *
 * @param inputLower The input string in lowercase
 * @return The type of interaction verb: 0 for no recognized verb, 1 for 'talk' or 'ask', 2 for 'kill', 3 for 'give'
 */
int World::DetectNpcVerb(string inputLower) {
    int verb = 0;

    //Talk Jimmy
    size_t talkPos = inputLower.find("talk");
    if (talkPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (talkPos + 5 >= inputLower.size()) ? ' ' : inputLower[talkPos + 5];
        if (std::isalpha(charAfter)) {

            verb = 1;

        }
        else {
            verb = 0;
        }
    }

    size_t askPos = inputLower.find("ask");
    if (askPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (askPos + 4 >= inputLower.size()) ? ' ' : inputLower[askPos + 4];
        if (std::isalpha(charAfter)) {

            verb = 1;

        }
        else {
            verb = 0;
        }
    }


    //Kill jimmy
    size_t killPos = inputLower.find("kill");
    if (killPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (killPos + 5 >= inputLower.size()) ? ' ' : inputLower[killPos + 5];
        if (std::isalpha(charAfter)) {
            verb = 2;

        }
        else {
            verb = 0;
        }
    }

    //GIVE THE DISH
    size_t givePos = inputLower.find("give");
    if (givePos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (givePos + 5 >= inputLower.size()) ? ' ' : inputLower[givePos + 5];
        if (std::isalpha(charAfter)) {
            verb = 3;

        }
        else {
            verb = 0;
        }
    }




    return verb;

}