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


World::World() {
    Room* startingRoom = new Room("Entrance Hall", "You are in the Entrance hall, there's nothig here to see.");
    Room* kitchen = new Room("Kitchen", "Here you can cook you som eggs and pasta that someone left on the fride, unless you are alergic to pasta, or eggs...");
    Room* livingRoom = new Room("Living Room", "Here is the heart of the house, wit conection with the entrance hall, the bathroom and Jimmy's bedroom.");
    Room* bedroom = new Room("Bedroom","Here is Jimmy lying in his bed, hes very bored, he wishes he could talk to somebody.");
    Room* bathroom = new Room("Bathroom", "A normal bathroom");

    Player*  player = new Player("You", "You are very handsome.",startingRoom);
    Npc* jimmy = new Npc("Jimmy", "He talks a lot, don't talk to him unless is absolutly necessary.", bedroom);
    jimmy->SetLines("Hey, I didn't see you, thank goodness you're here because I'm dying of boredom and I needed to talk to someone, how are you?");
    jimmy->SetLines(" Me not very well, the truth the other day my girlfriend and i broke up and it has made me think a lot about life and about what I'm going to do with it.");
    jimmy->SetLines(" The only thing that always cheers me up is a good egg pasta dish but only Jessica knew how to make it, even is only mix egg an pasta, by the way I have started to invest in NFT, what do you think? ");
    jimmy->SetLines(" I think I'm going to get rich in the future, and then you'll see how Jessica comes back,");
    jimmy->SetLines(" speaking of her, the last day we met she was wearing some nike sneakers from the flea market that looked really cool, I think I should talk to her again,");
    jimmy->SetLines(" you know, just to ask him about the shoes, nothing else, wow, talking so much makes you very hungry, don't you think so too? ");
    jimmy->SetLines(" What? You need to get in the bathroom? I have the key! Wow, that remembbers me of when... ");

    Item* egg = new Item("Egg","An egg, hopes nothing alive inside.", kitchen);
    Item* pasta = new Item("Pasta", "Pasta, you know ho loved pasta? I don't.", kitchen);
    Item* key = new Item("Key", "Key of the door in the bathroom", jimmy);

    Exit* exit1 = new Exit("south", "path to kitchen", startingRoom, kitchen);
    Exit* exit2 = new Exit("north", "path to entrance", kitchen, startingRoom);
    Exit* exit3 = new Exit("east", "path to living room", startingRoom, livingRoom);
    Exit* exit4 = new Exit("west", "path to entrance", livingRoom, startingRoom);
    Exit* exit5 = new Exit("east", "path to bedroom", livingRoom, bedroom);
    Exit* exit6 = new Exit("west", "path to living room", bedroom, livingRoom);
    Exit* exit7 = new Exit("north", "path living room and bathroom", livingRoom, bathroom);
    exit7->LockExit();

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

World::~World() {
    for (Entity* entity : entities) {
        delete entity;
    }
}

void World::Start() {
    Player* player = dynamic_cast<Player*>(entities[0]);

    // Show initial infrmation about bplayer and the room he is in
    if (player) {
        std::cout << player->GetName() << ": " << player->GetDescription() << std::endl;
    }
    else {
        std::cout << "No se ha encontrado el jugador en el mundo." << std::endl;
    }
    
    RoomDescription();
}

void World::RoomDescription() {
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    vector<string> neighbor;
    string direction;
    bool gameEnded = false;

    for (Entity* entity : entities) {
        Exit* exit = dynamic_cast<Exit*>(entity);
        if (exit) {
            if (exit->GetSource() == actualRoom) {
                std::cout << "  - At " << exit->GetName() << " is the " << exit->GetDestination()->GetName() << std::endl;
            }
            else if (actualRoom->GetName() == "Bathroom") {
                
                gameEnded = true;
            }
        }
    }
    if (gameEnded) {
        std::cout << "Ha acabado el juego!" << std::endl;
        exit(0);
    }

}
void World::RoomContainsSomething() {
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();

    for (Entity* entity : entities) {
        Item* item = dynamic_cast<Item*>(entity);
        Npc* npc = dynamic_cast<Npc*>(entity);
        if (item) {
            if (item->GetOwner() == actualRoom) {
                std::cout << "There's an item in this room: " << item->GetName() << std::endl;
                
            }
        }
        if (npc) {
            if (npc->GetRoom() == actualRoom) {
                std::cout << "There's someone in this room: " << npc->GetName() <<" (" << npc->GetDescription() << ")" << std::endl;

            }
        }
    }

}


bool World::LookRooms(string direction) {
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    string neighbor;
    int cont = 0;
    bool theresNeigbor = false;
    bool isLocked = false;
    bool hasKey = false;

    for (Entity* entity : entities) {
        Item* item = dynamic_cast<Item*>(entity);

        if (item) {
            if (item->GetName() == "Key" && item->GetOwner() == player) {
                hasKey = true;
            }
            
        }

    }


    for (Entity* entity : entities) {
        Exit* exit = dynamic_cast<Exit*>(entity);
        if (exit) {
            if (exit->IsLocked() && hasKey) {
                exit->UnlockExit();
            }
            if (exit->GetSource() == actualRoom) {
                //std::cout << "theresNeigbor " << exit->GetSource()->GetName() << std::endl;
              
                    if (direction == "north") {
                        if (exit->CheckDirection(NORTH)) {
                            if (!exit->IsLocked()) {
                                std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                                player->UpdateLocation(exit->GetDestination());
                                RoomDescription();
                                RoomContainsSomething();
                            }
                            else {
                                isLocked = true;
                                std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                            }

                        }



                    }
                    if (direction == "south") {
                        if (exit->CheckDirection(SOUTH)) {
                            if (!exit->IsLocked()) {
                                std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                                player->UpdateLocation(exit->GetDestination());
                                RoomDescription();
                                RoomContainsSomething();
                            }
                            else {
                                std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                            }

                        }



                    }

                    if (direction == "east") {

                        if (exit->CheckDirection(EAST)) {
                            if (!exit->IsLocked()) {
                                std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                                player->UpdateLocation(exit->GetDestination());
                                RoomDescription();
                                RoomContainsSomething();
                            }
                            else {
                                std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                            };

                        }



                    }

                    if (direction == "west") {

                        if (exit->CheckDirection(WEST)) {
                            if (!exit->IsLocked()) {
                                std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                                player->UpdateLocation(exit->GetDestination());
                                RoomDescription();
                                RoomContainsSomething();
                            }
                            else {
                                std::cout << exit->GetDestination()->GetName() << " is locked, you need a key. " << std::endl;
                            }

                        }



                    }
                
            }

        }
    
    }

    if (player->GetRoom() == actualRoom && !isLocked) {
        std::cout << "There's nothing in that direction "<< std::endl;
    }
   
    //std::cout << neighbor << std::endl;
    //theresNeigbor = MovePlayer(neighbor);

    return theresNeigbor;
}

void World::ProcessInput(string input) {
    string inputLower = input;
    int direction = 0;
    string dir;
    bool noRecognize = true;
    for (char& character : inputLower) {
        character = std::tolower(character);
    }

    //CHECK DIRECTIONS

    size_t northPos = inputLower.find("north");
    size_t southPos = inputLower.find("south");
    size_t eastPos = inputLower.find("east");
    size_t westPos = inputLower.find("west");
    
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

    //CHECK ITEMS

    size_t egg = inputLower.find("egg");
    size_t pasta = inputLower.find("pasta");
    size_t key = inputLower.find("key");
    string item;
    int verb = 0;
    string secondItem = "";

    if (egg != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (egg == 0) ? ' ' : inputLower[egg - 1];
        char charAfter = (egg + 4 >= inputLower.size()) ? ' ' : inputLower[egg + 4];
        if (!std::isalpha(charBefore)){// && !std::isalpha(charAfter)) {
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

    if (!LookItems(item, secondItem,verb) && verb != 0) {
        std::cout << "That item is not here" << std::endl;
    }

    item = "";

    int npcVerb = 0;

    //NPC INTERACIONS
    size_t jimmy = inputLower.find("jimmy");
    string npcName = "";
    if (jimmy != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (jimmy == 0) ? ' ' : inputLower[jimmy - 1];
        char charAfter = (jimmy + 5 >= inputLower.size()) ? ' ' : inputLower[jimmy + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            npcVerb = DetectNpcVerb(inputLower);
            if (npcVerb != 0) {
                npcName = "jimmy";
                noRecognize = false;
            }
        }
        else {
            noRecognize = true;
        }
    }

    if (jimmy != std::string::npos && pasta != std::string::npos) {
        char charBeforeJim = (jimmy == 0) ? ' ' : inputLower[jimmy - 1];
        char charAfterJim = (jimmy + 5 >= inputLower.size()) ? ' ' : inputLower[jimmy + 5];
        char charBeforePasta = (pasta == 0) ? ' ' : inputLower[pasta - 1];
        char charAfterPasta = (pasta + 5 >= inputLower.size()) ? ' ' : inputLower[pasta + 5];
        if (!std::isalpha(charBeforeJim) && !std::isalpha(charAfterJim) && !std::isalpha(charBeforePasta) && !std::isalpha(charAfterPasta)) {
            npcVerb = DetectNpcVerb(inputLower);
            if (npcVerb != 0) {
                npcName = "jimmy";
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


    

}

void World::InteractNpcs(string npcName, string itemName, int verb) {
    Player* player = dynamic_cast<Player*>(entities[0]);
    Npc* selectedNpc = dynamic_cast<Npc*>(entities[6]);
    Item* selectedItem = dynamic_cast<Item*>(entities[0]);
    Item* npcItem = dynamic_cast<Item*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    for (Entity* entity : entities) {
        Npc* npc = dynamic_cast<Npc*>(entity);
        
        if (npc) {
            if (npc->GetName() == npcName) {
                selectedNpc = npc;
            }
        }


    
    }


    if (selectedNpc) {

        for (Entity* entity : entities) {
            Item* item = dynamic_cast<Item*>(entity);
            if (item) {
                if (item->GetOwner()->GetName() == itemName) {
                    selectedItem = dynamic_cast<Item*>(item->GetOwner());
                    
                }
                if (item->GetOwner()->GetName() == selectedNpc->GetName()) {
                    npcItem = item;
                }

            }
        }


        if (player->GetRoom() == selectedNpc->GetRoom()) {
            if (verb == 1) {
                selectedNpc->ShowLines();
                std::cout << "Your thoughts: Wow, this is endless, bring him the damn egg pasta dish or kill him alredy." << std::endl;
            }
            if (verb == 2) {
                //Kill jimmy
                if (npcItem) {
                    npcItem->ChangeOwner(actualRoom);
                    std::cout << "The following itemwas droped: " << npcItem->GetName() << std::endl;
                }

                for (auto it = entities.begin(); it != entities.end(); ++it) {
                    Npc* npc = dynamic_cast<Npc*>(*it);
                    if (npc && npc == selectedNpc) { 
                        delete* it; 
                        entities.erase(it); 
                        break; 
                    }
                }

                std::cout << "Your thoughts: Omg, i wasn't serious, ok..." << std::endl;
            }
            if (verb == 3) {
                if (selectedItem) {
                    if (selectedItem->GetOwner() == player) {
                        selectedItem->ChangeOwner(selectedNpc);
                        std::cout << "You gave " << selectedItem->GetName() << " to " << selectedNpc->GetName() << std::endl;
                        std::cout << selectedNpc->GetName() << ": Wow, thanks! here you have: "<< std::endl;
                        if (npcItem) {
                            npcItem->ChangeOwner(player);
                            std::cout << selectedNpc->GetName() <<" gave you " << npcItem->GetName() << std::endl;
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
            std::cout << selectedNpc->GetName() << " is not here."<< std::endl;
        }

    }

}



bool World::LookItems(string itemName, string secondItem ,int verb) {
    
    Item* selectedItem = dynamic_cast<Item*>(entities[7]);
    Item* secondSelectedItem = dynamic_cast<Item*>(entities[7]);
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    bool theresItem = true;

    for (Entity* entity : entities) {
        Item* item = dynamic_cast<Item*>(entity);
        if (item) {
            if (item->GetName() == itemName) {
                selectedItem = item;
                
            }

            if (item->GetName() == secondItem) {
                //std::cout << "You mixed the item: " << item->GetName() << " with the following item: " << secondItem << std::endl;
                secondSelectedItem = item;
            }

        }   

    }

   
   if (selectedItem) {
        //GET ITEM
        if (verb == 1) {
            if (selectedItem->GetOwner() == actualRoom) {
                selectedItem->ChangeOwner(player);
                std::cout << "You picked the following item: " << selectedItem->GetName()  << " (" << selectedItem->GetDescription() << ")" << std::endl;
                theresItem = true;
            }
            else {
                
                theresItem = false;
            }
        }
        //DROP ITEMS
        else if (verb == 2) {
            if (selectedItem->GetOwner() == player) {
                selectedItem->ChangeOwner(actualRoom);
                std::cout << "You droped the following item: " << selectedItem->GetName() << std::endl;
                theresItem = true;
            }
            else {
                theresItem = false;
            }
        }
        //MIX ITEMS
        else if (verb == 3) {
            if (secondSelectedItem) {
                if (selectedItem->GetOwner() == player && secondSelectedItem->GetOwner() == player) {
                    selectedItem->ChangeOwner(secondSelectedItem);
                   std::cout << "You mixed the item: " << selectedItem->GetName() <<" with the following item: " << secondSelectedItem->GetName() <<  " now the item name is " << secondSelectedItem->GetName() <<std::endl;
                    theresItem = true;
                }
                else {
                    std::cout << "You don't have the items" << std::endl;
                }
            }
        }
    }
  



   /* if (theresItem) {
        RoomContainsSomething();
    }*/
    
    return theresItem;


}


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