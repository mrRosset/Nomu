#include "Kernel.h"
#include "E32Std.h"
#include "Emulator.h"
#include "Common/StringUtils.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Kernel {
	vir_add RHeap_ptr = 0;
	vir_add TrapHandler_ptr = 0;
}

void Kernel::ExecutiveCall(Emulator& emu, u32 number) {

	spdlog::get("console")->info("SWI {:x}", number);

	switch (number) {
	case 0x6C: User_Heap(emu); break;
	case 0x8D: User_LockedInc(emu); break;
	case 0x8E: User_LockedDec(emu); break;

	default:

		throw std::string("non-implemented executive call ") + std::to_string(number);
	}

}

void Kernel::User_Heap(Emulator& emu) {

	if (RHeap_ptr != 0) {
		emu.cpu->SetReg(0, RHeap_ptr);
		return;
	}

	RHeap_ptr = emu.mem->allocateRam(sizeof(RHeap));

	//TODO: Don't hardcode this
	//Corresponds to UserHeap::FixedHeap(void *, int)
	emu.ker_cpu->SetPC(0x503B1754);
	emu.ker_cpu->SetReg(Regs::LR, 0);
	emu.ker_cpu->SetReg(Regs::SP, emu.cpu->GetReg(Regs::SP));

	emu.ker_cpu->SetReg(0, RHeap_ptr);
	emu.ker_cpu->SetReg(1, 1052672); //Found in a test on the hardware

	emu.ker_cpu->call_stack.push_back(int_to_full_hex(emu.ker_cpu->GetPC()));

	//return value
	emu.cpu->SetReg(0, RHeap_ptr);

	emu.SetMode(Mode::Kernel);
}

void Kernel::User_LockedDec(Emulator& emu) {
	//TODO: Change if multithreading is implemented
	u32 value = emu.mem->read32(emu.cpu->GetReg(0));
	emu.mem->write32(emu.cpu->GetReg(0), value - 1);
	emu.cpu->SetReg(0, value);
}

void Kernel::User_LockedInc(Emulator& emu) {
	//TODO: Change if multithreading is implemented
	u32 value = emu.mem->read32(emu.cpu->GetReg(0));
	emu.mem->write32(emu.cpu->GetReg(0), value + 1);
	emu.cpu->SetReg(0, value);
}