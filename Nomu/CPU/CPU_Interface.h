#pragma once

#include <functional>
#include <vector>
#include "Common/Common.h"
#include "Memory/MemoryInterface.h"
#include "Tharm/Registers.h"
#include "Symbols/SymbolsManager.h"

class CPU_Interface {
public:
	MemoryInterface& mem;
	std::vector<std::string> call_stack;
	std::vector<std::string> function_trace;

	CPU_Interface(MemoryInterface& _mem) : mem(_mem), call_stack(), function_trace() {}
	virtual ~CPU_Interface() {}
	
	virtual void Step() {
		if (Symbols::hasFunctionName(GetPC())) {
			function_trace.push_back(Symbols::getFunctionNameOrElse(GetPC()));
		}
		ExecuteNextInstruction();
	}

	virtual u32 GetPC() = 0;
	virtual void SetPC(u32 addr) = 0;
	virtual u32 GetReg(int index) = 0;
	virtual void SetReg(int index, u32 value) = 0;
	virtual PSR& GetCPSR() = 0;
	virtual void SetCPSR(PSR& cpsr) = 0;

	//Callbacks
	std::function<void(u32 number)> swi_callback = nullptr;

protected:

	virtual void ExecuteNextInstruction() = 0;
};