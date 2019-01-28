#pragma once

#include "Memory_Interface.h"
#include "Constants.h"
#include <vector>
#include <iostream>
#include <fstream>

class GageMemory : public Memory_Interface {
public:

	std::vector<u8> user_data;
	std::vector<u8> rom;
	std::vector<u8> ram;
	u32 ram_cursor;

	GageMemory() : 
		user_data(USER_DATA_END - USER_DATA_START + 1), 
		rom(ROM_END - ROM_START + 1), 
		ram(RAM_END - RAM_START + 1) {
		ram_cursor = 15'0000;
	}

	inline u8 read8(u32 address) override {
		if (address >= USER_DATA_START && address <= USER_DATA_END) return user_data[address - USER_DATA_START];
		else if (address >= ROM_START && address <= ROM_END) return rom[address - ROM_START];
		else if (address >= RAM_START && address <= RAM_END) return ram[address - RAM_START];
		else throw (std::string("read to unmapped memory:") + std::to_string(address));
	}

	inline void write8(u32 address, u8 value) override {
		if (address >= USER_DATA_START && address <= USER_DATA_END) user_data[address - USER_DATA_START] = value;
		else if (address >= ROM_START && address <= ROM_END) rom[address - ROM_START] = value;
		else if (address >= RAM_START && address <= RAM_END) ram[address - RAM_START] = value;
		else throw (std::string("write to unmapped memory:") + std::to_string(address));
	}

	u32 allocateRam(u32 size) override {
		//TODO: is it an increasing or decreasing heap ?
		ram_cursor += size;
		return RAM_START + ram_cursor;
	}

	void loadRom(std::string& rom_path) override {
		std::ifstream stream(rom_path, std::ios::binary | std::ios::ate);

		if (!stream) {
			std::cerr << "Failed to open image file." << std::endl;
			return;
		}

		u64 length = stream.tellg();

		if (length > rom.size()) {
			std::cerr << "Rom dump is too big";
		}

		stream.seekg(0, std::ios::beg);

		if (!stream.read((char*)rom.data(), length))
		{
			throw std::string("Error reading bytes from file");
		}
		stream.close();
	}

};