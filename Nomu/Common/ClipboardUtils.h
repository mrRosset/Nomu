#pragma once

#include "Common.h"

#ifdef _MSC_VER
#include <windows.h>
#endif

void putInClipboard(const char* c, const size_t cSize)
{
#ifdef _MSC_VER
	std::wstring text(cSize, L'#');
	mbstowcs(&text[0], c, cSize);
	auto size = text.size() * sizeof(wchar_t);

	HGLOBAL hdst;
	LPWSTR dst;

	// Allocate string for cwd
	hdst = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, size + sizeof(wchar_t));
	dst = (LPWSTR)GlobalLock(hdst);
	memcpy(dst, text.c_str(), size + 1);
	dst[size] = 0;
	GlobalUnlock(hdst);

	// Set clipboard data
	if (!OpenClipboard(NULL))
		throw std::runtime_error("Clipboard error: " + GetLastError());
	EmptyClipboard();
	if (!SetClipboardData(CF_UNICODETEXT, hdst))
		throw std::runtime_error("Clipboard error: " + GetLastError());
	CloseClipboard();
#endif // _MSC_VER
}

void putInClipboard(const std::string& s) 
{
#ifdef _MSC_VER
	std::wstring text(s.begin(), s.end());
	auto size = text.size() * sizeof(wchar_t);

	HGLOBAL hdst;
	LPWSTR dst;

	// Allocate string for cwd
	hdst = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, size + sizeof(wchar_t));
	dst = (LPWSTR)GlobalLock(hdst);
	memcpy(dst, text.c_str(), size + 1);
	dst[size] = 0;
	GlobalUnlock(hdst);

	// Set clipboard data
	if (!OpenClipboard(NULL))
		throw std::runtime_error("Clipboard error: " + GetLastError());
	EmptyClipboard();
	if (!SetClipboardData(CF_UNICODETEXT, hdst))
		throw std::runtime_error("Clipboard error: " + GetLastError());
	CloseClipboard();
#endif // _MSC_VER
}

