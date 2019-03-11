#include <imgui/imgui.h>

#include "ControlsWindow.h"
#include "Emulator.h"

void ControlsWindow::render() {
	ImGui::Begin("Controls");
	if (ImGui::Button("Run"))
	{
		emu.state = EmuState::Running;
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		emu.state = EmuState::Stopped;
	}
	ImGui::SameLine();
	if (ImGui::Button("Step"))
	{
		emu.state = EmuState::Step;
	}

	ImGui::SameLine();

	// The scrolling needs to be performed later, once we have already created the disassembly window

	if (ImGui::Button("Go to PC"))
	{
		scroll_to_pc = true;
		emu.cpu->SetPC(emu.cpu->GetPC() + 4);
	}

	ImGui::SameLine();

	ImGui::Checkbox("Track PC", &track_pc);

	ImGui::SameLine();

	ImGui::Text(" %.3f ms/frame (%.1f fps)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}