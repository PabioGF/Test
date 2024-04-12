#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"

using namespace std;

string Entity::GetName() {
	return name;
}

string Entity::GetDescription() {
	return description;
}