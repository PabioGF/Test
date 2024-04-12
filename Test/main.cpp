#include <iostream>
#include <string>  
#include <conio.h>
#include "world.h"

using namespace std;

int main()
{
    World world;

    cout << "Welcome to Pablo's Zork!\n";
    world.Start();
    while (true) {
        string input;
        getline(cin, input);


        world.ProcessInput(input);

        if (input == "quit") {
            break;
        }
    }

    return 0;

}

