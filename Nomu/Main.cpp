#include <iostream>
#include <spdlog/spdlog.h>

#include "Symbols/SymbolsManager.h"
#include "Memory/GageMemory.h"
#include "Gui/Gui.h"

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

	std::cout << "Hello world !" << std::endl;

	GageMemory mem{};

	try {
		mem.read8(0x39);
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}

	Gui gui("Test"s, 1280, 720);

	while (gui.render());

	std::cin.get();
	return 0;
}