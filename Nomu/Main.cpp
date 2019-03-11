#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Gui/Gui.h"
#include "Emulator.h"

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
	Gui gui("", 1280, 720);

	while (gui.render()) {
		emu.Run();
	}

	return 0;
}