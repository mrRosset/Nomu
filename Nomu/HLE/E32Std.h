#pragma once

#include "Common/Common.h"

enum class CPUType : u32 {
	x86 = 0x1000,
	Arm = 0x2000,
	Mcore = 0x4000
};

enum class ProcessPriority
{
	Low = 150,
	Background = 250,
	Foreground = 350,
	High = 450,
	WindowServer = 650,
	FileServer = 750,
	RealTimeServer = 850,
	Supervisor = 950
};

//sizeof(RHeap) = 116
struct RHeap {

	//RHeapBase
	/*00*/ u32 iMinLength; // TInt
	/*04*/ u32 iMaxLength; // TInt
	/*08*/ u32 iOffset; // TInt
	/*12*/ u32 iGrowBy; // TInt
	/*16*/ u32 iAccessCount; // TInt
	/*20*/ u32 iType; // THeapType
	/*24*/ u32 iChunk; // RChunk
	/*28*/ u64 iLock; // RCriticalSection
	/*36*/ u32 iBase; // TUint8*
	/*40*/ u32 iTop; // TUint8*
	/*44*/ u32 iFree_len; // IFee is SCell
	/*48*/ u32 iFree_next;

	/*52*/ u32 vptr; // 

	/*56*/ u32 iTestCodeRunning; //TBool //it's supposed to be a bool. does it take the whole 4 bytes or only 1 ?
	/*60*/ s32 iTestNestingLevel; // TInt
	/*64*/ s32 iTestNumAllocCells; // TInt
	/*68*/ u32 iTestAddress; // TUint
	/*72*/ u32 iTestSize; // TInt
	/*76*/ u32 iTestAllocCount; // TInt
	/*80*/ u32 iNestingLevel; // TInt
	/*84*/ u32 iAllocCount; // TInt
	/*88*/ u32 iLevelNumAllocCells; //TInt
	/*92*/ u32 iPtrDebugCell; // SDebugCell*
	/*96*/ u32 iFailType; // TAllocFail
	/*100*/ u32 iFailRate; // TInt
	/*104*/ u32 iFailed; // TBool
	/*108*/ u32 iFailAllocCount; // TInt
	/*112*/ u32 iRand; // TInt
};