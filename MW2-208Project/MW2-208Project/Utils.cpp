#include "stdafx.h"
#include <Psapi.h>

#define RandomInt(min, max) (rand() % (max - min + 1) + min)
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
bool inited = false;

DWORD Utils::GetModuleBase(char* moduleName)
{
	HANDLE hSnap;
	MODULEENTRY32 xModule;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(GetCurrentProcess()));
	xModule.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &xModule)) {
		while (Module32Next(hSnap, &xModule)) {
			if (!strncmp((char*)xModule.szModule, moduleName, 8)) {
				CloseHandle(hSnap);
				return *(DWORD*)xModule.modBaseAddr;
			}
		}
	}
	CloseHandle(hSnap);
	return 0;
}
DWORD Utils::GetModuleSize(char* moduleName)
{
	HANDLE hSnap;
	MODULEENTRY32 xModule;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(GetCurrentProcess()));
	xModule.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &xModule)) {
		while (Module32Next(hSnap, &xModule)) {
			if (!strncmp((char*)xModule.szModule, moduleName, 8)) {
				CloseHandle(hSnap);
				return (DWORD)xModule.modBaseSize;
			}
		}
	}
	CloseHandle(hSnap);
	return 0;
}

const char* modulename = "iw4mp.exe";
DWORD modBase,modSiz;

DWORD Utils::FindPattern(char* pattern)
{
	const char* pat = pattern;
	DWORD firstMatch = 0;
	DWORD rangeStart = modBase;
	//DWORD rangeEnd = modBase + modSiz;

	const DWORD rangeEnd = 0x777777;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
		{
			//printf("%s -- 0x%x!\n", pattern,firstMatch);
			return firstMatch;
		}


		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
			{
				//printf("%s -- 0x%x!\n", pattern, firstMatch);
				return firstMatch;
			}

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = pattern;
			firstMatch = 0;
		}
	}
	printf("Failed to find pattern: %s\n", pattern);
	return NULL;
}

DWORD curSiz, curDLL;

DWORD Utils::GetCurrentModule()
{
	return curDLL;
}
DWORD Utils::GetCurrentModuleEnd()
{
	return curSiz;
}

bool Utils::ValidAddy(DWORD_PTR Addy)
{
	return (Addy > modBase && Addy < modSiz) || (Addy > curDLL && Addy < curSiz);
}

int Utils::UnprotectPE()
{

	// unprotect the entire PE
	HMODULE hModule = GetModuleHandle( nullptr );

	if ( !hModule ) {

		return ERROR_MOD_NOT_FOUND;
	}

	const auto header = reinterpret_cast< PIMAGE_DOS_HEADER >( hModule );

	const auto ntHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< uintptr_t >( hModule ) + header->e_lfanew );

	const SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;

	DWORD oProtect;

	VirtualProtect( static_cast< LPVOID >( hModule ), size, PAGE_EXECUTE_READWRITE, &oProtect );

	return ERROR_SUCCESS;
}

void Utils::Init(HMODULE thisModule)
{
	//credits to https://github.com/CamxxCore/PatchIWNet
	if (UnprotectPE() != ERROR_SUCCESS)
		return;

	// currentnetcode (test)
	*( DWORD* ) 0x4F3021 = 148;

	// bypass callback from IWSteamClient::OnLobbyCreated
	*( BYTE* ) 0x4DBFFD = 0x74;

	// bypass callback from IWSteamClient::JoinLobby
	*( BYTE* ) 0x4D3340 = 0x75;

	// steam check that is called each frame
	Utils::NOPAddy( 0x49D99F, 5 );

	*( int32_t* ) 0x4D8A8B = 0x79122C;

	curDLL = (DWORD)thisModule;
	MODULEINFO miModInfoo; GetModuleInformation(GetCurrentProcess(), (HMODULE)curDLL, &miModInfoo, sizeof(MODULEINFO));
	curSiz = curDLL + miModInfoo.SizeOfImage;

	modBase = (DWORD)GetModuleHandleA(modulename);
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)modBase, &miModInfo, sizeof(MODULEINFO));

	modSiz = modBase + miModInfo.SizeOfImage;
	inited = true;
}

void Utils::PatchAddy(DWORD_PTR Address, byte * buffer, size_t length)
{
	DWORD one, two;
	VirtualProtect((void*)Address, length, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)Address, buffer, length);
	VirtualProtect((void*)Address, length, one, &two);
}


void Utils::ReadAddy(DWORD_PTR Address, byte * buffer, size_t length)
{
	DWORD one, two;
	VirtualProtect((void*)Address, length, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)buffer, (void*)Address, length);
	VirtualProtect((void*)Address, length, one, &two);
}

void Utils::FillAddy(DWORD_PTR Address, byte value, size_t length)
{
	byte *buf = new byte[length];
	memset(buf, value, length);
	PatchAddy(Address, buf, length);
	delete[] buf;
}

void Utils::NOPAddy(DWORD_PTR Address, size_t length)
{
	FillAddy(Address, 0x90, length);
}
