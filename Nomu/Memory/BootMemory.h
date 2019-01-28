#pragma once

#include "Memory_Interface.h"
#include "Constants.h"
#include <vector>
#include <fstream>
#include <iostream>

class BootMemory : public Memory_Interface {
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
		else throw std::string("Invalid read to unmapped memory : ") + std::to_string(address);
	}

	inline void write8(u32 address, u8 value) override {
		if (address < rom.size()) rom[address] = value;
		else if (address >= KERNEL_DATA_START && address <= FAKE_KERNAL_DATA_END) kernel_data[address - KERNEL_DATA_START] = value;
		else throw std::string("Invalid write to unmapped memory: ") + std::to_string(address);
	}

	u32 allocateRam(u32 size) override {
		throw std::string("Cannot allocate memory in boot mem");
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