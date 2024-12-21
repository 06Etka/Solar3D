#ifndef UI_H
#define UI_H

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "window.h"

class UI
{
public:
	UI(Window& window);
	~UI();

	void update(float deltaTime);

private:
	void draw();

	float fps;
};

#endif // !UI_H
