#pragma once

#include <string>

struct TRomImage;
class MemoryInterface;

namespace TRomImageLoader
{
	void load(TRomImage& image, MemoryInterface& mem, std::string& lib_folder_path);
	void parse(std::string& path, TRomImage& image);
	void parseHeader(TRomImage& image);
	void parseExportDir(TRomImage& image);
	void checkHeaderValidity(TRomImage& image);
};