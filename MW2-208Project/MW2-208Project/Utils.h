#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class Utils
{
public:
	static DWORD GetModuleBase(char*);
	static DWORD GetModuleSize(char*);
	static DWORD GetCurrentModule();
	static DWORD GetCurrentModuleEnd();
	static int UnprotectPE( );

	static DWORD FindPattern(char* pattern);

	static void PatchAddy(DWORD_PTR Address, byte* buffer, size_t length);

	template<typename T>
	static void PatchAddy(DWORD_PTR Address, T buffer);


	static void ReadAddy(DWORD_PTR Address, byte* buffer, size_t length);

	template<typename T>
	static T ReadAddy(DWORD_PTR Address);

	static void FillAddy(DWORD_PTR Address, byte value, size_t length);
	static void NOPAddy(DWORD_PTR Address, size_t length);

	static bool ValidAddy(DWORD_PTR Address);

	static void Init(HMODULE thisModule);
};

template<typename T>
inline T Utils::ReadAddy(DWORD_PTR Address)
{
	T lol;
	ReadAddy(Address, &lol, sizeof(T));
	return lol;
}

template<typename T>
inline void Utils::PatchAddy(DWORD_PTR Address, T buffer)
{
	T buf2 = buffer;
	PatchAddy(Address, (byte*)&buf2, sizeof(T));
}