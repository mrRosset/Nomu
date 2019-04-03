#pragma once

#include <string>
#include <iomanip>
#include <sstream>

template< typename T >
std::string int_to_full_hex(T i)
{
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}

template< typename T >
std::string int_to_hex(T i)
{
	std::stringstream stream;
	stream << "0x" << std::hex << i;
	return stream.str();
}