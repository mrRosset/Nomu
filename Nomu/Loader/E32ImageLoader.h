#pragma once

#include <string>

struct E32Image;
class MemoryInterface;
class GuiMain;

namespace E32ImageLoader
{
	void load(E32Image& image, std::string file_name, MemoryInterface& mem, std::string& lib_folder_path);
	void parse(std::string& path, E32Image& image);
	void parseHeader(E32Image& image);
	void parseIAT(E32Image& image);
	void parseExportDir(E32Image& image);
	void parseImportSection(E32Image& image);
	void parseRelocSections(E32Image& image);
	void checkHeaderValidity(E32Image& image);
	void checkImportValidity(E32Image& image);
};