#pragma once

#include "Common/Common.h"

/*
From THC
+----------------------------+------------------------------------------------+
| 0x0040 0000 - 0x2FFF FFFF  : User Data                                      |
| 0x3000 0000 - 0x3FFF FFFF  : Static data for Java                           |
| 0x4000 0000 - 0x4000 1FFF  : Super page + CPU page                          |
| 0x4001 0000 - 0x4001 0FFF  : Shadow RAM page temporary address              |
| 0x4100 0000 - 0x4100 3FFF  : Page Directory                                 |
| 0x4108 0000 - 0x4108 3FFF  : Page table info                                |
| 0x4200 0000 - 0x423F FFFF  : Page tables                                    |
| 0x5000 0000 - 0x57FF FFFF  : ROM image                                      |
| 0x5800 0000 - 0x5EFF FFFF  : Memory-mapped I/O (danger!)                    |
| 0x5F00 0000 - 0x5FFF FFFF  : Video RAM (fun!)                               |
| 0x6000 0000 - 0x7FFF FFFF  : RAM                                            |
| 0x8000 0000 - 0xXXXX XXXX  : Kernel data/bss section                        |
| 0xXXXX XXXX - 0xXXXX XXXX  : Reentrant/IRQ/FIQ/Null/Exception kernel stack  |
| 0xXXXX XXXX - 0xXXXX XXXX  : Fixed chunks data for ROM fixed processes (?)  |
| 0xXXXX XXXX - 0xXXXX XXXX  : Kernel server heap and stack                   |
| 0xXXXX XXXX - 0xXXXX XXXX  : Home Section / All Processes                   |
| 0xXXXX XXXX - 0xXXXX XXXX  : RAM-loaded EXE & DLL code                      |
| 0xFFF0 0000 - 0xFFFE FFFF  : Void / Empty                                   |
| 0xFFFF 0000 - 0xFFFF FFFF  : Vectors (hoho!)                                |
+----------------------------+------------------------------------------------+
*/

enum MemoryLayout : u32 {
	USER_DATA_START      = 0x0040'0000,
	USER_DATA_END        = 0x2FFF'FFFF,
	ROM_START            = 0x5000'0000,
	ROM_END              = 0x57FF'FFFF,
	RAM_START            = 0x6000'0000,
	RAM_END              = 0x7FFF'FFFF,
	KERNEL_DATA_START    = 0x8000'0000,
	FAKE_KERNAL_DATA_END = 0x9000'0000,
};
