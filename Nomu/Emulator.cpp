#include "Emulator.h"

#include "CPU/Tharm/CPU.h"
#include "Memory/GageMemory.h"

Emulator::Emulator()
{
	mem = std::make_unique<GageMemory>();
	cpu = std::make_unique<CPU>(*mem);
	state = EmuState::Stopped;
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


