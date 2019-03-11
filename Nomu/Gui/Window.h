#pragma once

class Emulator;

class Window
{
public:
	Window(Emulator& emu_): emu(emu_){};
	~Window() {};
	virtual void render() = 0;

protected:
	Emulator& emu;
};

