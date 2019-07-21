#include <string>
#include <imgui/imgui.h>

#include "Common/ClipboardUtils.h"

void CopyableText(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	//UI textbox
	ImGui::TextV(fmt, args);

	//Own computation of text
	char buff[500];
	int size = vsnprintf(buff, 500, fmt, args);


	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
		putInClipboard(buff, size);
	}
	va_end(args);
}