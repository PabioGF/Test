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
	bool DetectDirectionVerb(string input);
	int DetectItemVerb(string input);
	int DetectNpcVerb(string input);
	void Start();
	bool LookRooms(string direction);
	bool LookItems(string item, string secondItem, int verb);
	void RoomDescription();
	void RoomContainsSomething();
	void InteractNpcs(string npc, string item, int verb);
	bool InputDirection(string inputLower);
	bool InputElement(string inputLower);

public:
	vector<Entity*> entities;
	

};
#endif // !EXIT