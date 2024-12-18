#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:
	Window();
	~Window();

	GLFWwindow* getWindow() const;
	int getWidth() const;
	int getHeight() const;

private:
	const int WIDTH = 1280;
	const int HEIGHT = 768;
	GLFWwindow* window;
};

#endif // !WINDOW_H
