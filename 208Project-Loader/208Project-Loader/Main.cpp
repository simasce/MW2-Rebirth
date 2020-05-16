#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <conio.h>

HANDLE getProcessHandle(const wchar_t* procName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (!wcscmp(entry.szExeFile, procName))
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				CloseHandle(snapshot);
				return hProcess;
			}
		}
	}

	CloseHandle(snapshot);
	return 0;
}

typedef LONG(__stdcall *NtSuspendProcess)(HANDLE ProcessHandle);
typedef LONG(__stdcall *NtResumeProcess)(HANDLE ProcessHandle);

bool pauseProcess(HANDLE process)
{
	NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtSuspendProcess");
	return pfnNtSuspendProcess(process) >= 0; // NT_SUCCESS
}

bool resumeProcess(HANDLE process)
{
	NtSuspendProcess pfnNtResumeProcess = (NtSuspendProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtResumeProcess");
	return pfnNtResumeProcess(process) >= 0; // NT_SUCCESS
}

void errorStop(const char* errorMsg)
{
	printf("Error: %s\n\n", errorMsg);
	printf("Press any key to close.\n");
	_getch();
	exit(0);
}

bool checkVersion(HANDLE procHandle)
{
	int protocolVersion = 0, gameVersion = 0;
	ReadProcessMemory(procHandle, (void*)0x4F3021, &protocolVersion, 4, 0);
	ReadProcessMemory(procHandle, (void*)0x431111, &gameVersion, 4, 0);
	return (protocolVersion == 145) && (gameVersion == 208);
}

DWORD DeadCrashes[] = { 0x4658D0, 0x47BC60 ,0x4AFFF0 ,0x4F2A30 ,0x47A550 ,0x4070F0 ,0x471C50 ,0x4F1650, 0x441BB0, 0x4AE3F0 };

void patchDeadCrashes(HANDLE procHandle)
{
	unsigned char jmp = 0xEB;
	for (int i = 0; i < 10; i++)
	{
		DWORD old1, old2;
		VirtualProtectEx(procHandle, (void*)(DeadCrashes[i] + 5), 1, PAGE_EXECUTE_READWRITE, &old1);
		WriteProcessMemory(procHandle, (void*)(DeadCrashes[i] + 5), &jmp, 1, 0);
		VirtualProtectEx(procHandle, (void*)(DeadCrashes[i] + 5), 1, old1, &old2);
	}
}

bool patchLoader(HANDLE procHandle, const char* dllPath)
{
	unsigned char loaderFunction[] =
	{
		0x68, 0x00, 0x00, 0x00, 0x00, // push dllPath
		0xFF, 0x15, 0xE0, 0x70, 0x6D, 0x00, // call dword ptr ds:0x6d70e0 (IAT: LoadLibraryA)
		0xC3 // ret
	};

	patchDeadCrashes(procHandle);

	DWORD allocatedMem = (DWORD)VirtualAllocEx(procHandle,0, MAX_PATH + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	DWORD allocatedExecutableMem = (DWORD)VirtualAllocEx(procHandle, 0, 12, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (!allocatedMem || !allocatedExecutableMem)
		return false;
	
	*(DWORD*)(&loaderFunction[1]) = allocatedMem;

	WriteProcessMemory(procHandle, (void*)allocatedMem, dllPath, MAX_PATH + 1, 0); //write dllpath
	WriteProcessMemory(procHandle, (void*)allocatedExecutableMem, loaderFunction, 12, 0); //write code

	DWORD diff = allocatedExecutableMem - (DWORD)0x46742C - 5;
	DWORD old1, old2;
	VirtualProtectEx(procHandle, (void*)0x46742C, 5, PAGE_EXECUTE_READWRITE, &old1);
	WriteProcessMemory(procHandle, (void*)0x46742D, &diff, 4, 0);
	VirtualProtectEx(procHandle, (void*)0x46742C, 5, old1, &old2);

	return true;
}

int main()
{
	char dllPath[MAX_PATH + 1];

	SetConsoleTitleA("MW2 208 Project -- Loader");

	printf("MW2 208 Project Loader by Simasce\n\n");

	FILE *dllFile = fopen("MW2-208Project.dll", "rb");
	if(!dllFile)
		errorStop("Could not find MW2-208Project.dll!");
	fclose(dllFile);

	GetFullPathNameA("MW2-208Project.dll", MAX_PATH, dllPath, 0);

	printf("Looking for 208 iw4mp.exe...");

	HANDLE procHandle = 0;
	while (!procHandle)
	{
		procHandle = getProcessHandle(L"iw4mp.exe");
		Sleep(10);
	}

	printf("Process found!\n");
	printf("\nPausing process...\n");
	if (!pauseProcess(procHandle))
		errorStop("Failed to stop the process!");

	printf("Process paused!\n");
	printf("Checking version...\n");
	if (!checkVersion(procHandle))
		errorStop("Wrong game version found!");

	printf("Version is correct!\n");
	printf("Patching loader code...\n");
	if (!patchLoader(procHandle, dllPath))
	{
		resumeProcess(procHandle);
		errorStop("Failed to patch process!");
	}

	printf("Game patched!\n");
	printf("Unpausing process...\n");
	if (!resumeProcess(procHandle))
		errorStop("Failed to resume the process!");

	printf("Done!\n");
	Sleep(800);
}