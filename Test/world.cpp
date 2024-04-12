#include <iostream>
#include <string>  
#include <conio.h>
#include "world.h"

using namespace std;

void World::ProcessInput(string input) {
    string inputLower = input;
    bool noRecognize = true;
    for (char& character : inputLower) {
        character = std::tolower(character);
    }


    size_t northPos = inputLower.find("north");
    size_t southPos = inputLower.find("south");
    size_t eastPos = inputLower.find("east");
    size_t westPos = inputLower.find("west");
    if (northPos != std::string::npos) {
        //Check if the word has spaces 
        char charBefore = (northPos == 0) ? ' ' : inputLower[northPos - 1];
        char charAfter = (northPos + 5 >= inputLower.size()) ? ' ' : inputLower[northPos + 5];
        if (!std::isalpha(charBefore) && !std::isalpha(charAfter)) {
            noRecognize = DetectVerb(inputLower);
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
            noRecognize = DetectVerb(inputLower);
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
            noRecognize = DetectVerb(inputLower);
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
            noRecognize = DetectVerb(inputLower);
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

    if (noRecognize) {
        std::cout << "Comando no reconocido." << std::endl;
    }

}

bool World::DetectVerb(string inputLower) {
    bool noRecognize = true;

    size_t goPos = inputLower.find("go");
    if (goPos != std::string::npos) {
        //Check if the word has spaces 
        char charAfter = (goPos + 5 >= inputLower.size()) ? ' ' : inputLower[goPos + 5];
        if (std::isalpha(charAfter)) {
            noRecognize = false;
            std::cout << "heading north" << std::endl;
        }
        else {
            std::cout << "hola" << std::endl;
            noRecognize = true;
        }
    }



    return noRecognize;

}