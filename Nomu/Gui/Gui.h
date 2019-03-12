#pragma once

#include <string>
#include <imgui/imgui_memory_editor.h>

#include "ControlsWindow.h"
#include "MemNavWindow.h"
#include "RegisterWindow.h"
#include "FunctionWindow.h"
#include "DisassemblyWindow.h"

struct MemoryEditor;
struct GLFWwindow;
class Emulator;

class Gui
{
public:
	Gui(Emulator& emu, std::string additional_title, int width, int height);
	~Gui();
	bool render();

private:
	int window_width;
	int window_height;
	bool scroll_to_pc = false;
	bool track_pc = true;
	GLFWwindow* window;
	ControlsWindow ctrl_window;
	MemNavWindow mem_nav_window;
	RegisterWindow reg_window;
	FunctionWindow fun_window;
	DisassemblyWindow dis_window;
	MemoryEditor mem_window;

	Emulator& emu;
};

