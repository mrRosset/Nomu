#pragma once

#include <vector>
#include "Common/StringUtils.h"
#include "MemoryInterface.h"
#include "MemoryConstants.h"

class TestMemory : public MemoryInterface {
public:
	std::vector<u8> ram;
	u32 ram_cursor;

	class TestMemory(u32 mem_size = 0x1000) : ram(mem_size) {
		ram_cursor = 0;
	}

	inline u8 read8(u32 address) override {
		if (address < ram.size()) return ram[address];
		else throw std::invalid_argument("Invalid read to unmapped memory: " + int_to_hex(address));
	}

	inline void write8(u32 address, u8 value) override {
		if (address < ram.size()) ram[address] = value;
		else throw std::invalid_argument("Invalid write to unmapped memory: " + int_to_hex(address));
	}

	u32 allocateRam(u32 size) override {
		ram_cursor += size;
		return RAM_START + ram_cursor;
	}

	std::vector<u8>& getDisplayMem() override {
		return ram;
	}

	u32 getDisplayMemBaseAddress() override {
		return 0;
	}

};