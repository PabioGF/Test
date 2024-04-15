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
    Room* startingRoom = new Room("Entrance Hall", "You are in the Entrance hall, there's nothig here to see.", "nothing","Kitchen", "Living Room", "nothing");
    Room* kitchen = new Room("Kitchen", "Here you can cook you som eggs and pasta that someone left on the fride, unless you are alergic to pasta, or eggs...", "Entrance Hall", "nothing", "nothing", "nothing");
    Room* livingRoom = new Room("Living Room", "Here is the heart of the house, wit conection with the entrance hall, the bathroom and Jimmy's bedroom.", "Bathroom", "nothing", "Bedroom", "Entrance Hall");
    Room* bedroom = new Room("Bedroom","Here is Jimmy lying in his bed, hes very bored, he wishes he could talk to somebody.", "nothing", "nothing", "nothing", "Living Room");
    Room* bathroom = new Room("Bathroom", "A normal bathroom", "nothing", "Living Room", "nothing", "nothing");

    Player*  player = new Player("You", "You are very handsome.",startingRoom);
    Npc* jimmy = new Npc("Jimmy", "He talks a lot, don't talk to him unless is absolutly necessary.", bedroom);
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
    neighbor.push_back(actualRoom->GetNorthNeighbor());
    neighbor.push_back(actualRoom->GetSouthNeighbor());
    neighbor.push_back(actualRoom->GetEastNeighbor());
    neighbor.push_back(actualRoom->GetWestNeighbor());
    std::cout << actualRoom->GetName() << ": " << actualRoom->GetDescription() << std::endl;

    RoomContainsSomething();

    for (int i = 0; i < neighbor.size(); i++) {
        if (strcmp(neighbor[i].c_str(), "nothing") != 0) {
            switch (i)
            {
            case 0:
                direction = "North";
                break;
            case 1:
                direction = "South";
                break;
            case 2:
                direction = "East";
                break;
            case 3:
                direction = "West";
                break;
            default:

                break;
            }

            std::cout << "  - At " << direction << " is the " << neighbor[i] << std::endl;
        }
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

bool World:: MovePlayer(string neighbor){
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* destination = dynamic_cast<Room*>(entities[1]);;
    bool theresNeighbor = true;
    
    if (strcmp(neighbor.c_str(), "nothing") == 0) {
        theresNeighbor = false;
    }
    else {
        if (strcmp(neighbor.c_str(), "Kitchen") == 0) {
            theresNeighbor = true;
            std::cout << "heading Kitchen" << std::endl;
            destination = dynamic_cast<Room*>(entities[2]);
        }
        if (strcmp(neighbor.c_str(), "Entrance Hall") == 0) {
            theresNeighbor = true;
            std::cout << "heading Entrance Hall" << std::endl;
            destination = dynamic_cast<Room*>(entities[1]);
        }
        if (strcmp(neighbor.c_str(), "Living Room") == 0) {
            theresNeighbor = true;
            std::cout << "heading Living Room"<< std::endl;
            destination = dynamic_cast<Room*>(entities[3]);
        }
        if (strcmp(neighbor.c_str(), "Bedroom") == 0) {
            theresNeighbor = true;
            std::cout << "heading Bedroom" << std::endl;
            destination = dynamic_cast<Room*>(entities[4]);
        }
        if (strcmp(neighbor.c_str(), "Bathroom") == 0) {
            theresNeighbor = true;
            std::cout << "heading Bathroom" << std::endl;
            destination = dynamic_cast<Room*>(entities[5]);
        }

        
    }

    return theresNeighbor;


}

bool World::LookRooms(string direction) {
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    string neighbor;
    int cont = 0;
    bool theresNeigbor = false;
   

    for (Entity* entity : entities) {
        Exit* exit = dynamic_cast<Exit*>(entity);
        if (exit) {
            if (exit->GetSource() == actualRoom) {
                //std::cout << "theresNeigbor " << exit->GetSource()->GetName() << std::endl;
                if (direction == "north") {
                    if (exit->CheckDirection(NORTH)) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                        player->UpdateLocation(exit->GetDestination());
                        RoomDescription();

                    }
                    
                    
                    
                }
                 if (direction == "south") {
                    if (exit->CheckDirection(SOUTH)) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                        player->UpdateLocation(exit->GetDestination());
                        RoomDescription();

                    }
                    
                    
                    
                }
         
                 if (direction == "east") {
                     
                    if (exit->CheckDirection(EAST)) {
                        std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                        player->UpdateLocation(exit->GetDestination());
                        RoomDescription();

                    }
                    
                    
                    
                }
                 
                 if (direction == "west") {

                     if (exit->CheckDirection(WEST)) {
                         std::cout << "heading " << exit->GetDestination()->GetName() << std::endl;
                         player->UpdateLocation(exit->GetDestination());
                         RoomDescription();

                     }



                 }
                
            }

        }
    
    }

    if (player->GetRoom() == actualRoom) {
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
        std::cout << "¡Saliendo del juego!" << std::endl;
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
            
            if (verb == 3) {
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

    if (noRecognize) {
        std::cout << "Comando no reconocido." << std::endl;
    }

    //NPC INTERACIONS
    size_t jimmy = inputLower.find("jimmy");

    if (jimmy != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (jimmy == 0) ? ' ' : inputLower[jimmy - 1];
        char charAfter = (jimmy + 5 >= inputLower.size()) ? ' ' : inputLower[jimmy + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            verb = DetectNpcVerb(inputLower);
            if (verb != 0) {
                noRecognize = false;
            }
        }
        else {

            noRecognize = true;
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
                   std::cout << "You mixed the item: " << selectedItem->GetName() <<" with the following item: " << secondSelectedItem->GetName() <<  "now the item name is " << secondSelectedItem->GetName() <<std::endl;
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




    return verb;

}