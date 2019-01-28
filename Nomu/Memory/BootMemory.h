#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "Common/StringUtils.h"
#include "MemoryInterface.h"
#include "Constants.h"

class BootMemory : public MemoryInterface {
public:

	std::vector<u8> kernel_data;
	std::vector<u8> rom;

	BootMemory() : 
		rom(ROM_END - ROM_START + 1),
		kernel_data(FAKE_KERNAL_DATA_END - KERNEL_DATA_START + 1)
	{}

	inline u8 read8(u32 address) override {
		if (address < rom.size()) return rom[address];
		else if (address >= KERNEL_DATA_START && address <= FAKE_KERNAL_DATA_END) return kernel_data[address - KERNEL_DATA_START];
		else throw std::invalid_argument("Invalid read to unmapped memory: " + int_to_hex(address));
	}

	inline void write8(u32 address, u8 value) override {
		if (address < rom.size()) rom[address] = value;
		else if (address >= KERNEL_DATA_START && address <= FAKE_KERNAL_DATA_END) kernel_data[address - KERNEL_DATA_START] = value;
		else throw std::invalid_argument("Invalid write to unmapped memory: " + int_to_hex(address));
	}

	u32 allocateRam(u32 size) override {
		throw std::runtime_error("Cannot allocate memory in boot mem");
	}

	void loadRom(std::string& rom_path) override {
		std::ifstream stream(rom_path, std::ios::binary | std::ios::ate);

		if (!stream) {
			throw std::invalid_argument("Failed to open Rom file");
		}

		u64 length = stream.tellg();

		if (length > rom.size()) {
			throw std::runtime_error("Rom dump size too big");
		}

		stream.seekg(0, std::ios::beg);

		if (!stream.read((char*)rom.data(), length))
		{
			throw std::runtime_error("Error reading bytes from file");
		}
		stream.close();
	}

};