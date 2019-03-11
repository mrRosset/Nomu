#pragma once

#include "CPU/CPU_Interface.h"
#include "Memory/MemoryInterface.h"

enum class EmuState { Stopped, Running, Step };

class Emulator
{
public:
	Emulator();
	~Emulator() {};

	void Run();

	EmuState state;
	std::unique_ptr<CPU_Interface> cpu;
	std::unique_ptr<MemoryInterface> mem;
};

