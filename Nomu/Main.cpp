#include <iostream>

#include "Memory/GageMemory.h"

int main(int argc, char *argv[])
{
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

