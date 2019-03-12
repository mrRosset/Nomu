#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Gui/Gui.h"
#include "Emulator.h"
#include "Memory/MemoryConstants.h"
#include "Symbols/SymbolsManager.h"

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

using namespace std::string_literals;


void emulate(std::string& app_path, std::string& lib_folder_path, std::string& rom_path) 
{
	Emulator emu;
	Gui gui(emu, "", 1200, 950);
	emu.cpu->SetPC(ROM_START);
	emu.LoadRom(rom_path);
	emu.LoadApp(app_path, lib_folder_path);

	//Main Loop
	while (gui.render()) {
		try {
			emu.Run();
		}
		catch (std::exception const& e)
		{
			std::cerr << "Error : " << e.what() << std::endl;
			emu.state = EmuState::Stopped;
		}
	}

}

int main(int argc, char *argv[])
{
	//Test Runner
	if (argc == 2 && argv[1] == "-t"s) {
		int result = Catch::Session().run(1, argv);
		std::cin.get();
		return 0;
	}

	if (argc < 5) {
		std::cerr << "Not enough arguments" << std::endl;
		return -1;
	}

	//Argument parsing
	std::string app_path = argv[1];
	std::string lib_folder_path = argv[2];
	std::string rom_path = argv[3];
	std::string symbols_folder_path = argv[4];

	//Setup Console
	auto console = spdlog::stdout_color_mt("console");
	// set the log pattern to [HH:MM:SS.nano]
	spdlog::set_pattern("[%T] [%l] %v");
	console->info("Start of the emulator");

	//Load Symbols if exists
	console->info("Loading Symbols");
	Symbols::load(symbols_folder_path);

	emulate(app_path, lib_folder_path, rom_path);

	return 0;
}