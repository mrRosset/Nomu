#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Common/StringUtils.h"
#include "Common/FileUtils.h"
#include "MemoryInterface.h"
#include "MemoryConstants.h"

class GageMemory : public MemoryInterface {
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
		else throw std::invalid_argument("read to unmapped memory: " + int_to_hex(address));
	}

	inline void write8(u32 address, u8 value) override {
		if (address >= USER_DATA_START && address <= USER_DATA_END) user_data[address - USER_DATA_START] = value;
		else if (address >= ROM_START && address <= ROM_END) rom[address - ROM_START] = value;
		else if (address >= RAM_START && address <= RAM_END) ram[address - RAM_START] = value;
		else throw std::invalid_argument("write to unmapped memory: " + int_to_hex(address));
	}

	u32 allocateRam(u32 size) override {
		//TODO: is it an increasing or decreasing heap ?
		ram_cursor += size;
		return RAM_START + ram_cursor;
	}

	void loadRom(std::string& rom_path) override {
		LoadFileInto(rom_path, rom);
	}

};