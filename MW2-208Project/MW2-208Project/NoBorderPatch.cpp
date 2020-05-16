#include "stdafx.h"

dvar_t* r_noborder = 0;

DWORD windowedWindowStyleHookLoc = 0x5083D3;
DWORD windowedWindowStyleHookJmpBack = 0x5083D8;
DWORD eaxSave = 0;

void __declspec(naked) Windowed_Hook()
{
	_asm mov eaxSave, eax;
	if (r_noborder->current.enabled)
	{
		__asm mov ebp, WS_VISIBLE | WS_POPUP
		__asm mov[esi + 10h], 0
		__asm mov[esi + 0Ch], 0
	}
	else
	{
		__asm mov ebp, WS_VISIBLE | WS_SYSMENU | WS_CAPTION
	}
	_asm mov eax, eaxSave;
	_asm jmp windowedWindowStyleHookJmpBack;
}

void NoBorderPatch::Hook()
{
	r_noborder = Engine->Dvar_RegisterBool("r_noborder", 0, 1, "Enables borderless mode.");
	DetourFunction((PBYTE)windowedWindowStyleHookLoc, (PBYTE)Windowed_Hook);
}