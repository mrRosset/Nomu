#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Gui/Gui.h"
#include "Emulator.h"
#include "Memory/MemoryConstants.h"

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

using namespace std::string_literals;

int main(int argc, char *argv[])
{
	//Test Runner
	if (argc == 2 && argv[1] == "-t"s) {
		int result = Catch::Session().run(1, argv);
		std::cin.get();
		return 0;
	}

	//Setup Console
	auto console = spdlog::stdout_color_mt("console");
	// set the log pattern to [HH:MM:SS.nano]
	spdlog::set_pattern("[%T] [%l] %v");
	console->info("Start of the emulator");

	Emulator emu;
	Gui gui(emu, "", 1280, 720);
	emu.cpu->SetPC(ROM_START);

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

	return 0;
}