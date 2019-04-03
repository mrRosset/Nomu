#pragma once

#include <string>
#include <vector>

#include "Common.h"

void LoadFileInto(std::string& rom_path, std::vector<u8>& data);
void LoadFile(std::string& rom_path, std::vector<u8>& data);
std::string extract_filename(const std::string& filepath);