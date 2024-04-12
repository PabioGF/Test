#pragma once
#include <vector>
#ifndef WORLD_HPP
#define WORLD_HPP


using namespace std;

class Entity;

class World {
public:
	void ProcessInput(string input);
	bool DetectVerb(string input);

private:
	vector<Entity*> entities;

};
#endif // !EXIT