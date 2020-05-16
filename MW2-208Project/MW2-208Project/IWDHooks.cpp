#include "stdafx.h"

/*
	MW2 ModLoader code
	Original authors: MW2EMP @ AgentGOD
	UC Forum Link: https://www.unknowncheats.me/forum/downloads.php?do=file&id=5511

	Reversed and ported code by Simasce 
*/

char *encBuffer = 0;

DWORD patchedloc_jmpback = 0x401BDD;
DWORD gscName = 0, scriptBufPointer = 0;
DWORD functionPatt = 0x4B42C0;

byte scriptBuffer[0x500000];
char curLink[256];

void __stdcall ReplacementFunction(int a1)
{
	FILE *fileBuf; // edi
	signed int v3; // esi
	signed int v4; // ecx
	char *v5; // eax
	int v6; // ebp
	char v7; // dl
	char v8; // [esp+7h] [ebp-105h]
	char DstBuf[260]; // [esp+8h] [ebp-104h]

	if (!Dvars->rebirth_mod)
	{
		scriptBufPointer = a1;
		return;
	}

	int modLen = strlen(Dvars->rebirth_mod->current.string);
	if (modLen == 0)
	{
		//no mod set
		scriptBufPointer = a1;
		return;
	}

	memset(DstBuf, 0, 260);
	sprintf_s(DstBuf, "%s\\mods\\%s\\%s.gsc", curLink, Dvars->rebirth_mod->current.string, gscName);

	fileBuf = fopen(DstBuf, "rb");
	if (fileBuf)
	{
		memset(scriptBuffer, 0, 0x500000u);
		v3 = 0;
		v8 = 0;
		fread(&v8, 1u, 1u, fileBuf);
		while (!feof(fileBuf))
		{
			if (!feof(fileBuf))
				scriptBuffer[v3++] = v8;
			fread(&v8, 1u, 1u, fileBuf);
		}
		if (scriptBuffer[0] == -1)
		{
			v4 = 0;
			if (v3 > 1)
			{
				v5 = (char*)scriptBuffer;
				v6 = v3 - 1;
				do
				{
					v7 = v5[1] ^ encBuffer[v4++];
					*v5 = ~v7;
					if (v4 >= 384)
						v4 = 0;
					++v5;
					--v6;
				} while (v6);
			}
			--v3;
		}
		scriptBuffer[v3] = 13;
		(scriptBuffer +	1)[v3] = 10;
		(scriptBuffer + 2)[v3] = 0;
		(scriptBuffer + 3)[v3] = 125;
		fclose(fileBuf);
		scriptBufPointer = (DWORD)scriptBuffer;
	}
	else
	{
		//printf("Not found: %s\n", DstBuf);
		scriptBufPointer = a1;
	}
	
}

__declspec(naked) void HookFunction()
{
	_asm
	{
		mov gscName, eax;
		call functionPatt;
		pushad;
		push eax;
		call ReplacementFunction;
		popad;
		mov eax, scriptBufPointer;
		jmp patchedloc_jmpback;
	}
}

void IWDHooks::Hook()
{
	encBuffer = (char*)ResourceLoader::loadResource(IDR_BINARY1, "Binary");
	if (!encBuffer)
		return;

	GetModuleFileNameA(0, curLink, 256);
	curLink[255] = 0;

	for (int i = strlen(curLink) - 1; i > 0; i--)
	{
		if (curLink[i] == '\\')
		{
			curLink[i] = 0;
			break;
		}
	}

	DetourFunction((PBYTE)0x401BD8, (PBYTE)HookFunction);
}