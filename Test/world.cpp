#include <iostream>
#include <string>  
#include <conio.h>
#include "world.h"
#include "room.h"
#include "creature.h"
#include "player.h"
#include "npc.h"
#include "item.h"

using namespace std;


World::World() {
    Room* startingRoom = new Room("Entrance Hall", "You are in the Entrance hall, there's nothig here to see.", "nothing","Kitchen", "Living Room", "nothing");
    Room* kitchen = new Room("Kitchen", "Here you can cook you som eggs and pasta that someone left on the fride, unless you are alergic to pasta, or eggs...", "Entrance Hall", "nothing", "nothing", "nothing");
    Room* livingRoom = new Room("Living Room", "Here is the heart of the house, wit conection with the entrance hall, the bathroom and Jimmy's bedroom.", "Bathroom", "nothing", "Bedroom", "Entrance Hall");
    Room* bedroom = new Room("Bedroom","Here is Jimmy lying in his bed, hes very bored, he wishes he could talk to somebody.", "nothing", "nothing", "nothing", "Living Room");
    Room* bathroom = new Room("Bathroom", "A normal bathroom except that, strangely enough, it has an exit door. Who puts an exit door in a bathroom? ", "nothing", "Living Room", "nothing", "nothing");



    Player*  player = new Player("You", "You are very handsome.",startingRoom);
    Npc* jimmy = new Npc("Jimmy", "He talks a lot, don't talk to him unless is absolutly necessary.", bedroom);
    Item* egg = new Item("Egg","An egg, hopes nothing alive inside.", kitchen);
    Item* pasta = new Item("Pasta", "Pasta, you know ho loved pasta? I don't.", kitchen);
    Item* key = new Item("Key", "Key of the door in the bathroom", jimmy);

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

        player->UpdateLocation(destination);
        RoomDescription();
    }

    return theresNeighbor;


}

bool World::LookRooms(int direction) {
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    string neighbor;
    bool theresNeigbor = true;
    switch (direction)
    {
    case 1:
        neighbor = actualRoom->GetNorthNeighbor();
        break;
    case 2:
        neighbor = actualRoom->GetSouthNeighbor();
        break;
    case 3:
        neighbor = actualRoom->GetEastNeighbor();
        break;
    case 4:
        neighbor = actualRoom->GetWestNeighbor();
        break;
    default:
        neighbor = "nothing";
        theresNeigbor = false;
        break;
    }
    //std::cout << neighbor << std::endl;
    theresNeigbor = MovePlayer(neighbor);

    return theresNeigbor;
}

void World::ProcessInput(string input) {
    string inputLower = input;
    int direction = 0;
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
            }
        }
        else {
            noRecognize = true;
        }
    }
    else if (eastPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (eastPos == 0) ? ' ' : inputLower[eastPos - 1];
        char charAfter = (eastPos + 5 >= inputLower.size()) ? ' ' : inputLower[eastPos + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectDirectionVerb(inputLower);
            if (!noRecognize) {
                direction = 3;
            }
        }
        else {
            noRecognize = true;
        }
    }
    else if (westPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (westPos == 0) ? ' ' : inputLower[westPos - 1];
        char charAfter = (westPos + 5 >= inputLower.size()) ? ' ' : inputLower[westPos + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectDirectionVerb(inputLower);
            if (!noRecognize) {
                direction = 4;
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
    if (!LookRooms(direction) && direction != 0) {
        std::cout << "There's nothing in that direction" << std::endl;
    }

    //CHECK ITEMS

    size_t egg = inputLower.find("egg");
    size_t pasta = inputLower.find("pasta");
    size_t key = inputLower.find("key");
    string item;
    int verb = 0;

    if (egg != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (egg == 0) ? ' ' : inputLower[egg - 1];
        //char charAfter = (egg + 5 >= inputLower.size()) ? ' ' : inputLower[egg + 5];
        if (!std::isalpha(charBefore)){// && !std::isalpha(charAfter)) {
            verb = DetectActionVerb(inputLower);
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
            verb = DetectActionVerb(inputLower);
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
        char charAfter = (key + 5 >= inputLower.size()) ? ' ' : inputLower[key + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            verb = DetectActionVerb(inputLower);
            if (verb != 0) {
                noRecognize = false;
                item = "Key";
            }
        }
        else {
            noRecognize = true;
        }
    }

    if (!LookItems(item, verb) && verb != 0) {
        std::cout << "That item is not here" << std::endl;
    }

    if (noRecognize) {
        std::cout << "Comando no reconocido." << std::endl;
    }
    

}
bool World::LookItems(string itemName, int verb) {
    Item* selectedItem = dynamic_cast<Item*>(entities[7]);;
    Player* player = dynamic_cast<Player*>(entities[0]);
    Room* actualRoom = player->GetRoom();
    bool theresItem = false;

    for (Entity* entity : entities) {
        Item* item = dynamic_cast<Item*>(entity);
        if (item) {
            if (item->GetName() == itemName) {
                selectedItem = item;
                
            }
        }
    }
    if (selectedItem) {
        //GET ITEM
        if (verb == 1) {
            if (selectedItem->GetOwner() == actualRoom) {
                selectedItem->ChangeOwner(player);
                std::cout << "You picked the following item: " << selectedItem->GetName() << std::endl;
                theresItem = true;
            }
            else {
                
                theresItem = false;
            }
        }
    }
    
    return theresItem;


}


bool World::DetectDirectionVerb(string inputLower) {
    bool noRecognize = true;

    size_t goPos = inputLower.find("go");
    if (goPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (goPos + 5 >= inputLower.size()) ? ' ' : inputLower[goPos + 5];
        if (std::isalpha(charAfter)) {
            noRecognize = false;
            
        }
        else {
            noRecognize = true;
        }
    }



    return noRecognize;

}

int World::DetectActionVerb(string inputLower) {
    int verb = 0;

    size_t goPos = inputLower.find("get");
    if (goPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (goPos + 5 >= inputLower.size()) ? ' ' : inputLower[goPos + 5];
        if (std::isalpha(charAfter)) {
            verb = 1;

        }
        else {
            verb = 0;
        }
    }



    return verb;

}