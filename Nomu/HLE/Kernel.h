#pragma once

#include "Common/Common.h"

class Emulator;

typedef u32 vir_add;

namespace Kernel {
	extern vir_add RHeap_ptr;
	extern vir_add TrapHandler_ptr;

	void ExecutiveCall(Emulator& emu, u32 number);

	void User_Heap(Emulator& emu);
	void User_LockedDec(Emulator& emu);
	void User_LockedInc(Emulator& emu);
}