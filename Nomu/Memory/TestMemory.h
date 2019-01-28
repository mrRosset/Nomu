#pragma once

#include "Memory_Interface.h"
#include "Constants.h"
#include <vector>

class TestMemory : public Memory_Interface {
public:
	std::vector<u8> ram;
	u32 ram_cursor;

	class TestMemory(u32 mem_size = 0x1000) : ram(mem_size) {
		ram_cursor = 0;
	}

	inline u8 read8(u32 address) override {
		if (address < ram.size()) return ram[address];
		else throw std::string("Invalid read to unmapped memory : ") + std::to_string(address);
	}

	inline void write8(u32 address, u8 value) override {
		if (address < ram.size()) ram[address] = value;
		else throw std::string("Invalid write to unmapped memory: ") + std::to_string(address);
	}

	u32 allocateRam(u32 size) override {
		ram_cursor += size;
		return RAM_START + ram_cursor;
	}

};