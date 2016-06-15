#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Vector2.h"

enum InputEvent
{
	MOVE_UP = 1,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	SHOOT
};

class Input
{
public:
	Input();
	~Input();
	void ProcessInput();
	bool KeyPressed(InputEvent input);
	Vector2* GetMousePosition();


private:
	Vector2* mousePosition;

	std::unordered_map<InputEvent, bool> keyStateMap;
};