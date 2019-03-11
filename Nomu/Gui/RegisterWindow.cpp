#include <imgui/imgui.h>

#include "RegisterWindow.h"
#include "CPU/Tharm/Disassembler/Disassembler.h"
#include "CPU/Tharm/Utils.h"
#include "Emulator.h"

void RegisterWindow::render() {
	
	auto& cpu = *emu.cpu;

	ImGui::Begin("Registers");
	for (u8 i = 0; i < 0xF; i++)
	{
		ImGui::Text("%s: ", Disassembler::Disassemble_Reg(i).c_str());
		ImGui::SameLine(38);
		ImGui::Text("0x%X", cpu.GetReg(i));
	}

	ImGui::Text("%s: ", Disassembler::Disassemble_Reg(0xF).c_str());
	ImGui::SameLine(38);
	ImGui::Text("0x%X", cpu.GetPC());

	ImGui::Text("CPSR: 0x%X", PSR_to_u32(cpu.GetCPSR()));
	ImGui::Text("N : %s", cpu.GetCPSR().flag_N ? "true" : "false");
	ImGui::Text("Z : %s", cpu.GetCPSR().flag_Z ? "true" : "false");
	ImGui::Text("C : %s", cpu.GetCPSR().flag_C ? "true" : "false");
	ImGui::Text("V : %s", cpu.GetCPSR().flag_V ? "true" : "false");
	ImGui::Text("I : %s", cpu.GetCPSR().flag_inter_I ? "true" : "false");
	ImGui::Text("F : %s", cpu.GetCPSR().flag_inter_F ? "true" : "false");
	ImGui::Text("T : %s", cpu.GetCPSR().flag_T ? "true" : "false");
	ImGui::End();
}