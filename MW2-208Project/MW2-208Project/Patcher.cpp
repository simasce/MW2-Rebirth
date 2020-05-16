#include "stdafx.h"

#define RegisterHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())

void * Patcher::DetourFunction(void * originalFunc, void * hookedFunc)
{
	RegisterHook(originalFunc, hookedFunc);
	return originalFunc;
}
