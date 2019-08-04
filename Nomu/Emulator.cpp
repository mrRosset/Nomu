#include "Emulator.h"

#include "HLE/E32Image.h"
#include "CPU/Tharm/CPU.h"
#include "CPU/Unicorn/CPUnicorn.h"
#include "Common/FileUtils.h"
#include "Memory/GageMemory.h"
#include "Loader/E32ImageLoader.h"
#include "Symbols/SymbolsManager.h"
#include "HLE/Kernel.h"

Emulator::Emulator()
{
	mem = std::make_unique<GageMemory>();
	cpu = std::make_unique<CPU>(*mem);
	ker_cpu = std::make_unique<CPU>(*mem);
	state = EmuState::Stopped;

	cpu->swi_callback = [&](u32 number) {
		Kernel::ExecutiveCall(*this, number);
	};
}

void Emulator::Run() {
	switch (state) {
	case EmuState::Step:
		cpu->Step();
		state = EmuState::Stopped;
		break;

	case EmuState::Running:
		cpu->Step();
		break;
	}
}

void Emulator::LoadRom(std::string& rom_path)
{
	mem->loadRom(rom_path);
}

void Emulator::LoadApp(std::string& app_path, std::string& lib_folder_path)
{
	E32Image image{};
	E32ImageLoader::parse(app_path, image);
	E32ImageLoader::load(image, extract_filename(app_path), *mem, lib_folder_path);

	auto dllEntry = image.header->code_base_address + image.header->entry_point_offset;
	auto mainEntry = image.header->code_base_address + image.code_section.export_directory[0];

	Symbols::addSymbol(dllEntry, "Dll Entry");
	Symbols::addSymbol(mainEntry, "App Entry");

	cpu->SetReg(Regs::SP, RAM_END);

	//Call one after the other
	cpu->SetPC(dllEntry);
	cpu->SetReg(Regs::LR, mainEntry);
}


