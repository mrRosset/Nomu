#pragma once

#include "Window.h"

class DisassemblyWindow : public Window
{
public:
	DisassemblyWindow(Emulator& emu, bool& scroll_to_pc_, bool& track_pc_) : 
		Window(emu),
		scroll_to_pc(scroll_to_pc_),
		track_pc(track_pc_) {};
	~DisassemblyWindow() {};
	void render() override;

private:
	bool& scroll_to_pc;
	bool& track_pc;
};

