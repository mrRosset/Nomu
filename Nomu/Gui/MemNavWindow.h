#pragma once

#include "Window.h"

class MemNavWindow : public Window
{
public:
	MemNavWindow(Emulator& emu_) : Window(emu_) {};
	~MemNavWindow() {};
	void render() override;
};

