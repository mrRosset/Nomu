#pragma once

#include "Window.h"

class RegisterWindow : public Window
{
public:
	RegisterWindow(Emulator& emu) : Window(emu) {};
	~RegisterWindow() {};
	void render() override;
};

