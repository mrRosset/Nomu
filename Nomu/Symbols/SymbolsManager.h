#pragma once

#include <string>
#include "Common/Common.h"

namespace Symbols {

	void load(std::string& folder_pathsymbols_folder_path);
	void addSymbol(u32 address, std::string text);
	bool hasFunctionName(u32 address);
	std::string getFunctionName(u32 address);
	std::string getFunctionNameOrElse(u32 address);
}