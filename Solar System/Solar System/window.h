#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:
	static Window& getInstance();
	~Window();

	void initialize();

	GLFWwindow* getWindow() const;
	int getWidth() const;
	int getHeight() const;

private:
	Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	const int WIDTH = 1280;
	const int HEIGHT = 768;
	GLFWwindow* window;
};

#endif // !WINDOW_H
