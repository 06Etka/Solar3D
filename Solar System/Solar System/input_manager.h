#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>

#include "window.h"

class InputManager
{
public:
	static InputManager& getInstance();

	void initialize();

	bool getKey(int key);
	bool getKeyDown(int key);
	bool getKeyUp(int key);

	void getMousePosition(double& xPos, double& yPos);

private:
	InputManager();

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	Window* window;

};

#endif // !INPUT_MANAGER_H