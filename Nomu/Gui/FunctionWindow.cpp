#include <imgui/imgui.h>

#include "FunctionWindow.h"
#include "CPU/Tharm/Disassembler/Disassembler.h"
#include "Emulator.h"

void FunctionWindow::render() {
	auto& cpu = *emu.cpu;

	ImGui::Begin("Functions Trace");
	ImGui::Columns(2, "Function trace");
	ImGui::SetColumnOffset(1, 50);
	ImGui::Text("#"); ImGui::NextColumn();
	ImGui::Text("function name"); ImGui::NextColumn();
	ImGui::Separator();

	ImGuiListClipper clipper(static_cast<int>(cpu.function_trace.size()), ImGui::GetTextLineHeight());

	for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
	{
		int ci = static_cast<int>(cpu.function_trace.size()) - i - 1;

		ImGui::Selectable(std::to_string(ci).c_str(), false, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick);
		ImGui::NextColumn();

		if (ci >= 0) {
			ImGui::Text(cpu.function_trace[ci].c_str());
		}
		else {
			ImGui::Text("");
		}
		ImGui::NextColumn();
	}
	clipper.End();
	ImGui::End();

}