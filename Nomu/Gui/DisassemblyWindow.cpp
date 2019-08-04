#include <imgui/imgui.h>

#include "DisassemblyWindow.h"
#include "CPU/Tharm/Disassembler/Disassembler.h"
#include "CPU/Tharm/Decoder/Decoder.h"
#include "Common/UiUtils.h"
#include "Emulator.h"

void DisassemblyWindow::render() {
	ImGui::Begin("Disassembly");

	auto& cpu = *emu.cpu;
	bool thumb = cpu.GetCPSR().flag_T;
	u8 instruction_bytes = thumb ? 2 : 4;

	ImGui::Columns(4, "Disassembly");
	ImGui::SetColumnOffset(1, 26);
	ImGui::SetColumnOffset(2, 108);
	ImGui::SetColumnOffset(3, thumb ? 158.f : 200.f);
	ImGui::Text(""); ImGui::NextColumn(); // To indicate a breakpoint
	ImGui::Text("Address"); ImGui::NextColumn();
	ImGui::Text("Bytes"); ImGui::NextColumn();
	ImGui::Text("Instruction"); ImGui::NextColumn();
	ImGui::Separator();

	u32 number_instructions_displayed = 0x2000;
	u32 offset = (s32(cpu.GetPC()) - s32(number_instructions_displayed / 2)) < 0 ? 0 : cpu.GetPC() - (number_instructions_displayed / 2);

	ImGuiListClipper clipper(number_instructions_displayed / instruction_bytes, ImGui::GetTextLineHeight()); // Bytes are grouped by four (the alignment for instructions

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImColor breakpoint_fill = ImColor(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	ImColor breakpoint_border = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImVec2 screen_cursor = ImGui::GetCursorScreenPos();

	// Perform scrolling, if necessary
	if (track_pc || scroll_to_pc)
	{
		ImGui::SetScrollFromPosY((((cpu.GetPC() - offset) / instruction_bytes) * ImGui::GetTextLineHeight()) - ImGui::GetScrollY(), 0.35f);
	}

	int label_lines = 0;

	for (s32 i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
	{
		u32 cur_address = (i - label_lines) * instruction_bytes + offset;

		screen_cursor = ImGui::GetCursorScreenPos();

		u32 symbol_addr = cur_address | (thumb ? 1 : 0);
		//Print symbols if found
		if (Symbols::hasFunctionName(symbol_addr)) {
			//empty line
			ImGui::Selectable("", false, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick);
			ImGui::NextColumn();
			CopyableText("0x%X", cur_address); ImGui::NextColumn();
			ImGui::Text(""); ImGui::NextColumn();
			ImGui::Text(""); ImGui::NextColumn();

			//line with function name
			ImGui::Selectable("", false, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick);
			ImGui::NextColumn();
			CopyableText("0x%X", cur_address); ImGui::NextColumn();
			ImGui::Text(""); ImGui::NextColumn();
			CopyableText(Symbols::getFunctionName(symbol_addr).c_str());  ImGui::NextColumn();
			label_lines += 2;
			i += 2;
		}

		if (ImGui::Selectable("", cpu.GetPC() == cur_address, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick))
		{
			cpu.breakpoint = cur_address;
		}

		if (cpu.breakpoint == cur_address)
		{
			// We use custom rendering for drawing the breakpoint
			draw_list->AddCircleFilled(ImVec2(screen_cursor.x + 6, screen_cursor.y + 7), 7, breakpoint_fill);
			draw_list->AddCircle(ImVec2(screen_cursor.x + 6, screen_cursor.y + 7), 7, breakpoint_border);
		}

		ImGui::NextColumn();
		ImGui::Text("0x%X", cur_address); ImGui::NextColumn();

		if (thumb)
		{
			try {
				CopyableText("%02X %02X", cpu.mem.read8(cur_address + 1), cpu.mem.read8(cur_address));
			}
			catch (...) {} // when in invalid memory space
		}
		else
		{
			try {
				CopyableText("%02X %02X %02X %02X", cpu.mem.read8(cur_address + 3), cpu.mem.read8(cur_address + 2), cpu.mem.read8(cur_address + 1), cpu.mem.read8(cur_address));
			}
			catch (...) {} // when in invalid memory space
		}

		ImGui::NextColumn();

		if (thumb)
		{

			IR_Thumb ir;
			ir.instr = TInstructions::SWI;
			std::string text = "";
			try {
				Decoder::Decode(ir, cpu.mem.read16(cur_address));
				text = Disassembler::Disassemble(ir);
			}
			catch (...) {}
			CopyableText("%s", text.c_str());
		}
		else
		{
			IR_ARM ir;
			ir.instr = AInstructions::SWI;
			std::string text = "";
			try {
				Decoder::Decode(ir, cpu.mem.read32(cur_address));
				text = Disassembler::Disassemble(ir);
			}
			catch (...) {}
			CopyableText("%s", text.c_str());
		}

		ImGui::NextColumn();

	}

	clipper.End();
	ImGui::End();
}