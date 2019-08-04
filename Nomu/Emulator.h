#pragma once

#include "CPU/CPU_Interface.h"
#include "Memory/MemoryInterface.h"

enum class EmuState { Stopped, Running, Step };
enum class Mode { User, Kernel };

class Emulator
{
public:
	Emulator();
	~Emulator() {};

	void Run();
	void SetMode(Mode new_mode);
	void LoadRom(std::string& rom_path);
	void LoadApp(std::string& app_path, std::string& lib_folder_path);

	EmuState state;
	Mode mode;

	std::unique_ptr<CPU_Interface> user_cpu;
	std::unique_ptr<CPU_Interface> ker_cpu;
	CPU_Interface* cpu;
	std::unique_ptr<MemoryInterface> mem;
};

