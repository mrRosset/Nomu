#pragma once

#include "Common.h"

u16 crc16_ccitt(u8(&values)[6]);

inline void u8_from_32(u8 output[4], u32 value)
{
	output[0] = (u8)value;
	output[1] = (u8)(value >>= 8);
	output[2] = (u8)(value >>= 8);
	output[3] = (u8)(value >>= 8);
}

template <class T>
inline bool getFlagBit(T v, unsigned bit_number) {
	return ((v >> bit_number) & 0b1);
}
template <class T>
inline bool getFlagBit(T v, u64 bit_number) {
	return ((v >> bit_number) & 0b1);
}
template <class T>
inline bool getFlagBit(T v, signed bit_number) {
	if (bit_number < 0) throw std::runtime_error("not yet implemented");
	return ((v >> bit_number) & 0b1);
}
//avoid implicit conversions
template <class T, class U>
bool getFlagBit(T, U) = delete;


template <class T>
inline unsigned getBit(T v, unsigned bit_number) {
	return ((v >> bit_number) & 0b1);
}
template <class T>
inline unsigned getBit(T v, u64 bit_number) {
	return ((v >> bit_number) & 0b1);
}
template <class T>
inline unsigned getBit(T v, signed bit_number) {
	if (bit_number < 0) throw std::runtime_error("not yet implemented");
	return ((v >> bit_number) & 0b1);
}
//avoid implicit conversions
template <class T, class U>
unsigned getBit(T, U) = delete;


inline u32 getHi(u64 result) {
	return (result >> 32) & 0xFFFFFFFF;
}

inline u32 getLo(u64 result) {
	return result & 0xFFFFFFFF;
}

inline s32 getHi(s64 result) {
	return (result >> 32) & 0xFFFFFFFF;
}

inline s32 getLo(s64 result) {
	return result & 0xFFFFFFFF;
}

//avoid implicit conversions
template <class T>
u32 getHi(T) = delete;

template <class T>
u32 getLo(T) = delete;