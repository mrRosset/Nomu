#include <iostream>
#include <fstream>
#include <string>

#include "FileUtils.h"


void LoadFileInto(std::string& rom_path, std::vector<u8>& data) {
	std::ifstream stream(rom_path, std::ios::binary | std::ios::ate);

	if (!stream) {
		throw std::invalid_argument("Failed to open file " + rom_path);
	}

	u64 length = stream.tellg();

	if (length > data.size()) {
		throw std::runtime_error("File is too big for memory buffer " + rom_path);
	}

	stream.seekg(0, std::ios::beg);

	if (!stream.read((char*)data.data(), length))
	{
		throw std::runtime_error("Error reading bytes from file " + rom_path);
	}
	stream.close();
}

void LoadFile(std::string& rom_path, std::vector<u8>& data) {
	std::ifstream stream(rom_path, std::ios::binary | std::ios::ate);

	if (!stream) {
		throw std::invalid_argument("Failed to open file " + rom_path);
	}

	u64 length = stream.tellg();
	data.resize(length);

	if (length > data.size()) {
		throw std::runtime_error("File is too big for memory buffer " + rom_path);
	}

	stream.seekg(0, std::ios::beg);

	if (!stream.read((char*)data.data(), length))
	{
		throw std::runtime_error("Error reading bytes from file " + rom_path);
	}
	stream.close();
}

std::string extract_filename(const std::string& filepath) {
	auto pos = filepath.rfind("\\");
	if (pos == std::string::npos)
		pos = -1;
	return std::string(filepath.begin() + pos + 1, filepath.end());
}