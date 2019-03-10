#include <iostream>
#include <spdlog/spdlog.h>

#include "Memory/GageMemory.h"
#include "Symbols/SymbolsManager.h"


#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

int main(int argc, char *argv[])
{
	//Test Runner
	if (argc == 2 && argv[1] == std::string("-t") ) {
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


	std::cin.get();
	return 0;
}