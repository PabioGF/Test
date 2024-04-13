#pragma once
#include <vector>
#ifndef WORLD_HPP
#define WORLD_HPP


using namespace std;

class Entity;

class World {
public:
	World();
	~World();
	void ProcessInput(string input);
	bool DetectVerb(string input);
	void Start();
	bool MovePlayer(string neighbor);
	bool LookRooms(int direction);
	void RoomDescription();

public:
	vector<Entity*> entities;

};
#endif // !EXIT