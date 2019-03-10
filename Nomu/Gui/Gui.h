#pragma once

#include <string>
#include <imgui/imgui.h>

struct GLFWwindow;

class Gui
{
public:
	Gui(std::string additional_title, int width, int height);
	~Gui();
	bool render();

private:
	int window_width;
	int window_height;
	GLFWwindow* window;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

