#pragma once

#include "Window.h"

class FunctionWindow : public Window
{
public:
	FunctionWindow(Emulator& emu) : Window(emu) {};
	~FunctionWindow() {};
	void render() override;
};

