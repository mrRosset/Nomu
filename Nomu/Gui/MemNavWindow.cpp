#include <imgui/imgui.h>

#include "MemNavWindow.h"
#include "Emulator.h"

void MemNavWindow::render() {
	ImGui::Begin("Memory Viewer");
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImGuiStyle& style = ImGui::GetStyle();
	ImColor col = style.Colors[ImGuiCol_Border];
	const ImVec2 p = ImGui::GetCursorScreenPos();

	draw_list->AddLine(ImVec2(p.x, p.y + 17), ImVec2(p.x + 800, p.y + 17), col, 1);
	draw_list->AddLine(ImVec2(p.x, p.y + 10), ImVec2(p.x, p.y + 24), col, 1);
	draw_list->AddLine(ImVec2(p.x + 799, p.y + 10), ImVec2(p.x + 799, p.y + 24), col, 1);

	draw_list->AddText(ImVec2(p.x, p.y + 30), ImColor(255, 255, 255, 255), "0x0");
	draw_list->AddText(ImVec2(p.x + 720, p.y + 30), ImColor(255, 255, 255, 255), "0xFFFF'FFFF");


	//draw_list->AddLine(ImVec2(p.x + 150, p.y + 10), ImVec2(p.x + 150, p.y + 24), col, 1);
	draw_list->AddLine(ImVec2(p.x + 250, p.y + 10), ImVec2(p.x + 250, p.y + 24), col, 1);
	draw_list->AddLine(ImVec2(p.x + 275, p.y + 10), ImVec2(p.x + 275, p.y + 24), col, 1);
	draw_list->AddText(ImVec2(p.x + 252, p.y - 3), ImColor(255, 255, 255, 255), "Rom");

	float cursor_x = p.x + u64(emu.cpu->GetPC()) / float(0xFFFF'FFFF) * 800.0f;
	float cursor_y = p.y + 19;
	draw_list->AddTriangleFilled(ImVec2(cursor_x, cursor_y), ImVec2(cursor_x - 4, cursor_y + 7), ImVec2(cursor_x + 4, cursor_y + 7), ImColor(255, 255, 255, 255));
	ImGui::End();
}
