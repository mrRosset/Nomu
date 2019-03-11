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
	void LoadRom(std::string& rom_path);
	void LoadApp(std::string& app_path, std::string& lib_folder_path);

	EmuState state;
	std::unique_ptr<CPU_Interface> cpu;
	std::unique_ptr<MemoryInterface> mem;
};

