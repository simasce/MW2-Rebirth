#include "stdafx.h"
#include <intrin.h>

typedef int(__cdecl* tMSG_ReadBitsCompress)(int a1, byte *a2, int a3);
tMSG_ReadBitsCompress oMSG_ReadBitsCompress;

typedef void(__cdecl* tPartyHost_HandleJoinPartyRequest)(PartyData_s* party, int localControllerIndex, netadr_t from, void* msg);
tPartyHost_HandleJoinPartyRequest oPartyHost_HandleJoinPartyRequest;

void hk_PartyHost_HandleJoinPartyRequest(PartyData_s* party, int localControllerIndex, netadr_t from, msg_t* msg)
{
	if (msg->cursize > 55)
		return;

	oPartyHost_HandleJoinPartyRequest(party, localControllerIndex, from, msg);
}

//MSG_ReadBitsCompress RCE fix
int hk_MSG_ReadBitsCompress(int a1, byte* a2, int a3)
{
	//a2 is switched with a3 in 211

	//a4 is 0x20000 in CL_ParseServerMessage (0x481750)
	//a4 is 0x800 in  SV_ExecuteClientMessage (0x4F2A80)
	int a4;
	DWORD ret = (DWORD)_ReturnAddress();
	if (ret == 0x48181B)
		a4 = 0x20000;
	else if (ret == 0x4F2AD7)
		a4 = 0x800;
	else
		return oMSG_ReadBitsCompress(a1, a2, a3); // this shouldn't happen
 

	byte *v3; // ebp
	int v4; // edi
	bool v5; // zf
	bool v6; // sf
	byte *v7; // esi

	int indx = 0;

	v3 = a2;
	v4 = 8 * a3;
	v5 = 8 * a3 == 0;
	v6 = 8 * a3 < 0;
	v7 = a2;
	a3 = 0;

	if (v6 || v5)
		return 0;

	while (indx < a4)
	{
		Engine->Com_DecompressWithZLib(*(DWORD**)0x1D128C8, (int *)&a2, a1, &a3);
		*(byte*)((DWORD)v7 + (DWORD)indx) = (byte)a2;
		indx++;

		if (a3 >= v4)
			return indx;
	}
	return -1;
}


//SV_AuthClient RCE Fix

DWORD SV_AuthClient_Ret, SV_AuthClient_Ret2 = 0x4D633A;
__declspec(naked) void Mhk_SV_AuthClient()
{
	_asm
	{
		cmp eax, 0x800;
		ja  isRCE;
		jmp SV_AuthClient_Ret;

	isRCE:
		add esp, 8;
		jmp  SV_AuthClient_Ret2;
	}
}


void RCEFixes::Init()
{
	oPartyHost_HandleJoinPartyRequest = (tPartyHost_HandleJoinPartyRequest)DetourFunction((PBYTE)0x5B5EC0, (PBYTE)hk_PartyHost_HandleJoinPartyRequest);
	oMSG_ReadBitsCompress = (tMSG_ReadBitsCompress)DetourFunction((PBYTE)0x47B7F0, (PBYTE)hk_MSG_ReadBitsCompress);
	SV_AuthClient_Ret = (DWORD)DetourFunction((PBYTE)0x4D62D1, (PBYTE)Mhk_SV_AuthClient); //works
}