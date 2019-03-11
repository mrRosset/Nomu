#include "ControlsWindow.h"

#include <imgui/imgui.h>


void ControlsWindow::render() {
	ImGui::Begin("Controls");
	if (ImGui::Button("Run"))
	{
		//emu.state = CPUState::Running;
	}

	ImGui::SameLine();

	if (ImGui::Button("Pause"))
	{
		//emu.state = CPUState::Stopped;
	}

	ImGui::SameLine();

	if (ImGui::Button("Step"))
	{
		//emu.state = CPUState::Step;
	}

	ImGui::SameLine();

	// The scrolling needs to be performed later, once we have already created the disassembly window
	bool scroll_to_pc = false;

	if (ImGui::Button("Go to PC"))
	{
		scroll_to_pc = true;
		//emu.getCPU().SetPC(emu.getCPU().GetPC() + 4);
	}

	ImGui::SameLine();

	bool track_pc = true;
	ImGui::Checkbox("Track PC", &track_pc);

	ImGui::SameLine();

	ImGui::Text(" %.3f ms/frame (%.1f fps)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}