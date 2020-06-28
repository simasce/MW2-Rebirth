#include "stdafx.h"
#include <algorithm>
#include <intrin.h>
#include <map>
#include <vector>

char ScrambleBuf[0x620B];
char *ProgramBuf = 0;

class msg_extension
{
public:
	msg_extension()
	{
		a10 = (int)ScrambleBuf;
	}
	DWORD a10 = (int)ScrambleBuf;
	DWORD a11 = 0xFF;
	DWORD curTick = 0;
};

std::map<char*, msg_extension> MSGMap;

DWORD* getClient(int clientID)
{
	return (DWORD*)(((DWORD)0x3231F10) + (DWORD)(0x299E4 * clientID));
}

DWORD_PTR CL_SendServerMessageSwitches[] = { 0x4818CD , 0x4818A3 , 0x4818AE , 0x48191C , 0x4818DC };
DWORD_PTR SendServerMessage_SwitchAddy = 0x48198C;

typedef char(__cdecl* tsub_454310)(char* a1, char *a2, signed int a3);
tsub_454310 sub_454310 = (tsub_454310)0x454310;

typedef int(__cdecl* tI_strncmp)(char *a1, char *a2, int size);
tI_strncmp I_strncmp = (tI_strncmp)0x4C05F0;

typedef char *(__cdecl* tI_strncpyz)(char *destination, char *source, int length);
tI_strncpyz I_strncpyz = (tI_strncpyz)0x5C1C20;

typedef void(__cdecl* tOutputToConsole_Format)(int type, char *arg4, ...);
tOutputToConsole_Format OutputToConsole = (tOutputToConsole_Format)0x42C640;

typedef msg_t* (__cdecl* tsub_4C2920)(msg_t* a1, float a2);
tsub_4C2920 osub_4C2920;

typedef int(__cdecl* tMSG_Init)(msg_t *Dst, int a2, int a3);
tMSG_Init oMSG_Init;

typedef int*(__cdecl* tMSG_BeginReading)(msg_t* msg);
tMSG_BeginReading oMSG_BeginReading;

typedef int(__cdecl* tMSG_ReadString)(msg_t *a1, int a2, unsigned int a3);
tMSG_ReadString oMSG_ReadString;

typedef int(__cdecl* tMSG_ReadByte)(msg_t *a1);
tMSG_ReadByte oMSG_ReadByte;

typedef DWORD *(__cdecl* tMSG_ReadLong)(msg_t *a1);
tMSG_ReadLong oMSG_ReadLong;

typedef signed int(__cdecl* tMSG_ReadShort)(msg_t *a11);
tMSG_ReadShort oMSG_ReadShort;

typedef int(__cdecl* tMSG_ReadStringLine)(msg_t *a1, int a2, unsigned int a3);
tMSG_ReadStringLine oMSG_ReadStringLine;

typedef void(__cdecl* tMSG_SetDefaultUserCmd)(int a1, DWORD *a2);
tMSG_SetDefaultUserCmd oMSG_SetDefaultUserCmd;

typedef int(__cdecl* tMSG_Discard)(int a1);
tMSG_Discard oMSG_Discard;

typedef char(__cdecl* tI_CleanChar)(char a1);
tI_CleanChar I_CleanChar = (tI_CleanChar)0x486B40;

typedef int(__cdecl* tSomeMSGClamp)(int a2, int a3, int a4, int a5);
tSomeMSGClamp SomeMSGClamp = (tSomeMSGClamp)0x465E40;

typedef char *(__cdecl* tScr_GetScrambleBuf)(unsigned int a1);
tScr_GetScrambleBuf oScr_GetScrambleBuf;

typedef int(__cdecl* tMSG_WriteShort)(msg_t* a11, __int16 a2);
tMSG_WriteShort oMSG_WriteShort;

typedef char(__cdecl* tMSG_WriteByte)(msg_t *a11, char a2);
tMSG_WriteByte oMSG_WriteByte;

typedef char(__cdecl* tMSG_WriteString)(msg_t* a11, char *Source);
tMSG_WriteString oMSG_WriteString;

typedef int(__cdecl* tMSG_WriteLong)(msg_t* a11, int a2);
tMSG_WriteLong oMSG_WriteLong;

typedef int(__cdecl* tSV_SendServerCommandInner)(DWORD *client, signed int a2, char* message);
tSV_SendServerCommandInner oSV_SendServerCommandInner;

typedef void(__cdecl* tSV_ExecuteClientMessage)(DWORD* client, DWORD *a2);
tSV_ExecuteClientMessage oSV_ExecuteClientMessage;

typedef int(__cdecl* tsub_624560)(DWORD* client, msg_t* msg);
tsub_624560 osub_624560;

typedef DWORD *(__cdecl* tCmd_TokenizeStringNoEval)(char* str);
tCmd_TokenizeStringNoEval oCmd_TokenizeStringNoEval;

typedef int(__cdecl* tCL_CGameNeedsServerCommand)(int a1, int a2);
tCL_CGameNeedsServerCommand oCL_CGameNeedsServerCommand;

typedef int(__cdecl* tR_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float angle, const RGBA_COLOR* color, int material);
tR_AddCmdDrawStretchPic oR_AddCmdDrawStretchPic;

typedef char *(__cdecl* tSV_Cmd_ArgvBuffer)(int a1, char *a2, int a3);
tSV_Cmd_ArgvBuffer SV_Cmd_ArgBuf = (tSV_Cmd_ArgvBuffer)0x4F21D0;

typedef char(__cdecl* tMSG_WriteDeltaPlayerState)(int a1, msg_t *msg, int a3, char *a4, int a5);
tMSG_WriteDeltaPlayerState oMSG_WriteDeltaPlayerState;

typedef void(__cdecl* tClientCommand)(int a1);
tClientCommand oClientCommand;

typedef void(__cdecl *tSV_ExecuteClientCommand)(const char *s, int clientOK, int fromOldServer);
tSV_ExecuteClientCommand oSV_ExecuteClientCommand;

struct a11Param //to force default 0
{
	DWORD a11 = 0;
	a11Param() {}
	a11Param(DWORD A11) : a11(A11) {}
	void operator= (const DWORD &eq) { a11 = eq; }
	void operator= (const a11Param &eq) { *this = eq; }
};

std::map<DWORD, a11Param> a11Map;
std::vector<DWORD> a11Extras = 
{
	0x60F6F6,
	0x60F867,
	0x60F9ED,
	0x60FB63,
	0x60FC24,
	0x60FD09,
	0x60FD39,
	0x60FE39,
	0x60FE44,
	0x60FE4F,
	0x60FF5E,
	0x6100F4,
	0x610145,
	0x4153D4,
	0x4153E9,
	0x4153FE,
	0x415413,
	0x4157D7
};

DWORD GetA11(DWORD retAddy, msg_t* curMsg)
{
	if (MSGMap[curMsg->data].a11 != 0xFF)
		return MSGMap[curMsg->data].a11;

	auto &a = std::find(a11Extras.begin(), a11Extras.end(), retAddy);
	if(a != a11Extras.end())
		return curMsg->data == 0 ? 0 : 4;

	return a11Map[retAddy].a11;
}

void LoadA11()
{
	//208 clientside a11s done
	a11Map[0x443935] = 0x5;
	a11Map[0x443969] = 0x9;
	a11Map[0x443981] = 0x9;
	a11Map[0x443A53] = 0x9;
	a11Map[0x443ACB] = 0x9;
	a11Map[0x443ADC] = 0x9;
	a11Map[0x443AED] = 0x9;
	a11Map[0x443AFD] = 0x9;
	a11Map[0x49A9F3] = 0x9;
	a11Map[0x4B6EFD] = 0x9;
	a11Map[0x4B6F0D] = 0x9;
	a11Map[0x4B70FE] = 0x9;
	a11Map[0x4B712B] = 0x9;
	a11Map[0x4B7186] = 0x9;

	a11Map[0x4B7E02] = 0xb; //test fix -- was commented out
	
	//208 serverside and leftover clientside 
	a11Map[0x5DFD63] = 0x4;
	a11Map[0x47107B] = 0x4;
	a11Map[0x4B728A] = 0x9;
	a11Map[0x4B72B7] = 0x9;
	a11Map[0x4B73D7] = 0x9;
	a11Map[0x60F79B] = 0x4;
	a11Map[0x624573] = 0x4;
	a11Map[0x624584] = 0x4;
	a11Map[0x624594] = 0x4;
	a11Map[0x6245A4] = 0x4;
	a11Map[0x6245B0] = 0x4;
	a11Map[0x6245B8] = 0x4;
	a11Map[0x62468D] = 0x4;
	a11Map[0x624818] = 0x4;
	a11Map[0x62483B] = 0x4;
	a11Map[0x624848] = 0x4;
	a11Map[0x624850] = 0x4;
	a11Map[0x45410B] = 0x4;
	a11Map[0x454116] = 0x4;
	a11Map[0x42F0DA] = 0x4;
	a11Map[0x42F0E6] = 0x4;
	a11Map[0x42F0ED] = 0x4;
	a11Map[0x42F17B] = 0x4;
	a11Map[0x418258] = 0x4;
	a11Map[0x41825F] = 0x4;
	a11Map[0x418278] = 0x4;
	a11Map[0x46AA4A] = 0x4;
}

char GSSCMap[128];
char GSSCMap_Server[128];

char GSSCMap_CGNSC[128];
char GSSCMap_CGNSC_Server[128];

void LoadGSSCMap()
{
	memset(GSSCMap, 0, 128);
	memset(GSSCMap_Server, 0, 128);
	memset(GSSCMap_CGNSC, 0, 128);
	memset(GSSCMap_CGNSC_Server, 0, 128);

	//211 to 208
	GSSCMap['w'] = 'A';
	GSSCMap['x'] = 'B';
	GSSCMap['y'] = 'C';
	GSSCMap['z'] = 'D';
	GSSCMap['A'] = 'E';
	GSSCMap['B'] = 'F';
	GSSCMap['C'] = 'G';
	GSSCMap['D'] = 'H';
	GSSCMap['E'] = 'I';
	GSSCMap['F'] = 'J';
	GSSCMap['H'] = 'L';
	GSSCMap['J'] = 'N';
	GSSCMap['K'] = 'O';
	GSSCMap['M'] = 'Q';
	GSSCMap['N'] = 'R';
	GSSCMap['O'] = 'S';
	GSSCMap['P'] = 'T';
	GSSCMap['Q'] = 'U';
	GSSCMap['R'] = 'V';
	GSSCMap['S'] = 'W';
	GSSCMap['U'] = 'h';
	GSSCMap['V'] = 'i';
	GSSCMap['h'] = 'k';
	GSSCMap['i'] = 'l';
	GSSCMap['j'] = 'm';
	GSSCMap['k'] = 'n';
	GSSCMap['l'] = 'o';
	GSSCMap['m'] = 'p';
	GSSCMap['n'] = 'q';
	GSSCMap['o'] = 'r';
	GSSCMap['p'] = 's';
	GSSCMap['q'] = 't';
	GSSCMap['r'] = 'u';
	GSSCMap['s'] = 'v';
	GSSCMap['u'] = 'x';
	GSSCMap['v'] = 'y';
	
	//GSSCMap['k'] = 'B';
	//GSSCMap['x'] = 'n';
	GSSCMap['t'] = 'w';

	GSSCMap_CGNSC['k'] = 'B';
	GSSCMap_CGNSC['x'] = 'n';
	GSSCMap_CGNSC['t'] = 'w';

	for (int i = 'A'; i <= 'z'; i++)
	{
		GSSCMap_Server[GSSCMap[i]] = i;
	}

	for (int i = 'A'; i <= 'z'; i++)
	{
		GSSCMap_CGNSC_Server[GSSCMap_CGNSC[i]] = i;
	}
}

void PatchGSSC()
{
	Utils::PatchAddy<byte>(0x595943, 0x90);
	Utils::PatchAddy<byte>(0x595944, 0xC3);
}

struct CustomActionIndex //to force default 0
{
	int andx = -1;
	CustomActionIndex() {}
	CustomActionIndex(int aindx) : andx(aindx) {}
	void operator= (const int &eq) { andx = eq; }
	void operator= (const CustomActionIndex &eq) { *this = eq; }
	bool operator <(const CustomActionIndex &indx) const
	{
		return andx < indx.andx;
	}
};

std::map<std::string, CustomActionIndex> ActionMap;
std::map<CustomActionIndex, std::string> ActionMap_Inverse;
void LoadActionMap()
{
	ActionMap["+attack"] = 1;
	ActionMap["-attack"] = 2;
	ActionMap["+melee"] = 3;
	ActionMap["-melee"] = 4;
	ActionMap["+frag"] = 5;
	ActionMap["-frag"] = 6;
	ActionMap["+smoke"] = 7;
	ActionMap["-smoke"] = 8;
	ActionMap["+breath_sprint"] = 9;
	ActionMap["-breath_sprint"] = 10;
	ActionMap["+usereload"] = 11;
	ActionMap["-usereload"] = 12;
	ActionMap["+speed_throw"] = 13;
	ActionMap["-speed_throw"] = 14;
	ActionMap["+actionslot 1"] = 15;
	ActionMap["-actionslot 1"] = 16;
	ActionMap["+actionslot 2"] = 17;
	ActionMap["-actionslot 2"] = 18;
	ActionMap["+actionslot 3"] = 19;
	ActionMap["-actionslot 3"] = 20;
	ActionMap["+actionslot 4"] = 21;
	ActionMap["-actionslot 4"] = 22;
	ActionMap["+stance"] = 23;
	ActionMap["-stance"] = 24;
	ActionMap["+gostand"] = 25;
	ActionMap["-gostand"] = 26;
	ActionMap["+forward"] = 27;
	ActionMap["-forward"] = 28;
	ActionMap["+back"] = 29;
	ActionMap["-back"] = 30;
	ActionMap["+moveleft"] = 31;
	ActionMap["-moveleft"] = 32;
	ActionMap["+moveright"] = 33;
	ActionMap["-moveright"] = 34;
	ActionMap["+movedown"] = 35;
	ActionMap["-movedown"] = 36;
	ActionMap["+left"] = 37;
	ActionMap["-left"] = 38;
	ActionMap["+right"] = 39;
	ActionMap["-right"] = 40;
	ActionMap["+lookup"] = 41;
	ActionMap["-lookup"] = 42;
	ActionMap["+lookdown"] = 43;
	ActionMap["-lookdown"] = 44;
	ActionMap["+strafe"] = 45;
	ActionMap["-strafe"] = 46;
	ActionMap["+holdbreath"] = 47;
	ActionMap["-holdbreath"] = 48;
	ActionMap["+activate"] = 49;
	ActionMap["-activate"] = 50;
	ActionMap["+reload"] = 51;
	ActionMap["-reload"] = 52;
	ActionMap["+prone"] = 53;
	ActionMap["-prone"] = 54;
	ActionMap["+mlook"] = 55;
	ActionMap["-mlook"] = 56;
	ActionMap["+toggleads_throw"] = 57;
	ActionMap["-toggleads_throw"] = 58;
	ActionMap["+sprint"] = 59;
	ActionMap["-sprint"] = 60;
	ActionMap["+scores"] = 61;
	ActionMap["-scores"] = 62;
	ActionMap["+talk"] = 63;
	ActionMap["-talk"] = 64;
	ActionMap["togglemenu"] = 65;
	ActionMap["weapnext"] = 66;
	ActionMap["pause"] = 67;
	ActionMap["chatmodepublic"] = 68;
	ActionMap["chatmodeteam"] = 69;
	ActionMap["weapprev"] = 70;
	ActionMap["centerview"] = 71;
	ActionMap["togglecrouch"] = 72;
	ActionMap["toggleprone"] = 73;
	ActionMap["goprone"] = 74;
	ActionMap["gocrouch"] = 75;
	ActionMap["toggleads"] = 76;
	ActionMap["leaveads"] = 77;

	for (auto a = ActionMap.begin(); a != ActionMap.end(); a++)
	{
		ActionMap_Inverse[a->second] = a->first;
	}
}
int GetActionIndex(char* Action)
{
	CustomActionIndex a = ActionMap[std::string(Action)];
	return a.andx;
}

char clientMSGBuf[254], clientMSGBuf2[254];
char* Process_ClientMessage(char* clientMSG)
{
	memset(clientMSGBuf, 0, 254);
	memset(clientMSGBuf2, 0, 254);

	if (strlen(clientMSG) >= 254)
		return clientMSG;

	if (clientMSG[0] != 'n' || clientMSG[1] != 't' || clientMSG[2] != ' ')
	{
		if (!strcmp(clientMSG, "score"))
		{
			clientMSG[1] = 0; //score -> s
		}
		return clientMSG;
	}

	strcpy(clientMSGBuf2, clientMSG + 3);

	int actionIndex = GetActionIndex(clientMSGBuf2);
	if (actionIndex == -1)
		return clientMSG;

	sprintf(clientMSGBuf, "n %i", actionIndex);
	strcpy(clientMSG, clientMSGBuf);

	return clientMSGBuf;
}

char servMSGBuf[254], servMSGBuf2[254];
char* oldMSGBuf = 0;

char* SV_Process_ClientMessage(char* clientMSG)
{
	oldMSGBuf = 0;
	if (!I_strncmp("n ", clientMSG, 2))
	{
		memset(servMSGBuf, 0, 254);
		memset(servMSGBuf2, 0, 254);
		strcpy(servMSGBuf2, clientMSG + 2);

		int ll = (int)strtol(servMSGBuf2, 0, 10);
		std::string action = ActionMap_Inverse[ll];
		if (action.empty())
			return 0;

		sprintf(servMSGBuf, "nt %s", action.c_str());
		oldMSGBuf = clientMSG;
		return servMSGBuf;
	}
	else if (!I_strncmp("s", clientMSG, 2))
	{
		memset(servMSGBuf, 0, 254);
		sprintf(servMSGBuf, "score");
		oldMSGBuf = clientMSG;
		return servMSGBuf;
	}

	return 0;
}

DWORD lastScramble = 0;
char *__cdecl Scr_GetScrambleBuf(unsigned int a1)
{
	char* scrambleRet = (char*)(ProgramBuf + 16 * (a1 % 0x620B));
	lastScramble = a1;

	return scrambleRet;
}

DWORD esiBak = 0;
char __cdecl hk_MSG_WriteString(msg_t* a11, char *Source)
{
	_asm mov esiBak, esi;

	if ((DWORD)_ReturnAddress() == 0x443981)
	{
		Process_ClientMessage(Source);
	}

	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);

	DWORD* a1 = (DWORD*)a11;
	signed int v2; // eax
	signed int v3; // esi
	signed int v4 = (int)a1; // eax
	int v5; // esi
	signed int v6; // ebp
	int i; // eax
	char *v8; // ebx
	unsigned int v9; // esi
	char v10; // al
	int v11; // ecx
	int v12; // esi
	signed int v14; // [esp+10h] [ebp-40Ch]
	char Dest[1024]; // [esp+1Ch] [ebp-400h]

	v2 = strlen(Source);
	v3 = v2;
	v14 = v2;
	if (v2 < 1024)
	{
		v6 = 0;
		if (v2 > 0)
		{
			for (i = Source - Dest; ; i = Source - Dest)
			{
				v8 = &Dest[v6];
				v9 = v6 + a11->cursize - curA11;
				v10 = I_CleanChar(Dest[v6++ + i]);
				*v8 = (v9 < 0x10) * *(BYTE *)((v9 & 0xF) + MSGMap[a11->data].a10) + v10;
				if (v6 >= v14)
					break;
			}
			v3 = v14;
		}
		v11 = a11->cursize;
		Dest[v6] = ((unsigned int)(v6 + a11->cursize - curA11) < 0x10)	* *(BYTE *)((((BYTE)v6 + a11->cursize - curA11) & 0xF) + MSGMap[a11->data].a10);
		v4 = v3 + 1;
		v12 = v11 + v3 + 1;
		if (v12 > a11->maxsize)
		{
			a11->overflowed;
		}
		else
		{
			v4 = sub_454310(v11 + a11->data, Dest, v4);
			a11->cursize = v12;
		}
	}
	else
	{
		v4 = (unsigned int)I_strncpyz(Dest, Source, 896);
		v5 = a11->cursize;
		if (v5 >= a11->maxsize)
		{
			a11->overflowed;
		}
		else
		{
			v4 = ((unsigned int)(v5 - curA11) < 0x10)	* *(BYTE *)((((BYTE)v5 - curA11) & 0xF) + MSGMap[a11->data].a10);
			*(BYTE *)(v5 + a11->data) = v4;
			a11->cursize++;
		}
	}

	_asm mov esi, esiBak;

	return v4;
}

int getMagicScramble()
{
	DWORD msBackup = *(DWORD*)0x6320D04;
	_asm
	{
		pushad;

		mov ecx, msBackup;
		mov eax, 0x51EB851F;
		imul ecx;
		sar edx, 4;
		mov eax, edx;
		shr eax, 0x1F;
		add eax, edx;
		push eax;
		call Scr_GetScrambleBuf;
		add esp, 4;
		mov msBackup, eax;
		popad;
	}
	return msBackup;
}

DWORD *oldLongClient=0;
int __cdecl hk_MSG_WriteLong(msg_t* a11, int a2)
{

	DWORD retAddy = (DWORD)_ReturnAddress();

	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);
	DWORD* a1 = (DWORD*)a11;

	int result; // eax
	int v3; // ecx

	result = (int)a1;
	v3 = a11->cursize;
	if (v3 + 4 > a11->maxsize)
	{
		a11->overflowed = 1;
	}
	else
	{
		*(DWORD *)(v3 + a11->data) = a2 + *(DWORD *)((((BYTE)v3 - curA11) & 0xC) + MSGMap[a11->data].a10) * ((unsigned int)(v3 - curA11) < 0x10);
		a11->cursize = v3 + 4;
	}

	switch (retAddy)
	{
	case 0x443924:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(*(DWORD*)0xA45274);
		break;
	case 0x443935:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(*(DWORD*)0xA45274 + ((*(DWORD*)0xA45278) << 8));
		break;
	case 0x5A7893:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(*(DWORD*)0xA2526C);
		break;
	case 0x5A78AE:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(*(DWORD*)0xA2526C + ((*(DWORD*)0xA45278) << 8));
		break;
	case 0x624992:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(a2);
		break;
	case 0x42F0E6:
		//MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf((*(DWORD*)0x6320D04) / 50);
		MSGMap[a11->data].a10 = getMagicScramble();
		break;
	case 0x41825F:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(a2);
		break;
	case 0x4B38BE:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(a2);
		break;
	case 0x4A4C9D:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(a2);
		MSGMap[a11->data].a11 = a11->cursize;
		break;
	case 0x46AA9A:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(a2);
		MSGMap[a11->data].a11 = a11->cursize; //test fix
		break;
	case 0x452D33:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf(a2);
		break;
	case 0x624584:
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf((oldLongClient[33703]) + ((oldLongClient[33687]) << 8));
		break;
	default:
		break;
	}

	return result;
}

int __cdecl hk_MSG_WriteShort(msg_t* a11, __int16 a2)
{

	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);
	DWORD* a1 = (DWORD*)a11;
	int result; // eax
	int v3; // edx

	result = (int)a1;
	v3 = a11->cursize;
	if (v3 + 2 > a11->maxsize)
	{
		a11->overflowed = 1;
	}
	else
	{
		*(WORD *)(v3 + a11->data) = a2	+ *(WORD *)((((BYTE)v3 - curA11) & 0xE) + MSGMap[a11->data].a10)	* ((unsigned int)(v3 - curA11) < 0x10);
		a11->cursize = v3 + 2;
	}
	return result;
}


char __cdecl hk_MSG_WriteByte(msg_t *a11, char a2)
{
	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);
	DWORD* a1 = (DWORD*)a11;
	int v2; 
	char result=a2; 

	v2 = a11->cursize;
	if (v2 >= a11->maxsize)
	{
		a11->overflowed = 1;
	}
	else
	{
		result = a2 + ((unsigned int)(v2 - curA11) < 0x10) * *(BYTE *)(MSGMap[a11->data].a10 + (((BYTE)v2 - curA11) & 0xF));
		DWORD writePTR = (DWORD)(v2 + a11->data);
		*(BYTE *)(writePTR) = result;
		a11->cursize++;
	}


	return result;
}

signed int __cdecl hk_MSG_ReadShort(msg_t *a11)
{
	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);
	DWORD* a1 = (DWORD*)a11;
	DWORD *v1; // esi
	int v2; // eax
	int v3; // edi
	__int16 v4; // cx
	__int16 v5; // dx
	signed int result; // eax

	v1 = a1;
	v2 = a1[5] + a1[6];
	v3 = a1[7];
	if (v3 + 2 > v2)
	{
		*a1 = 1;
		result = -1;
	}
	else
	{

		_asm pushad;
		_asm mov eax, v2;
		SomeMSGClamp((int)a1, v3, (int)&a1, 2);
		_asm popad;

		DWORD bugAddy = ((((BYTE)v3 - curA11) & 0xE) + MSGMap[a11->data].a10);
		if (Utils::ValidAddy(bugAddy))
		{
			v4 = *(WORD *)bugAddy * ((unsigned int)(v3 - curA11) < 0x10);
		}
		else
		{
			v4 = 0;
		}

		v5 = (signed __int16)a1;
		v1[7] = v3 + 2;
		result = (signed __int16)(v5 - v4);
	}

	return result;
}



int hk_MSG_ReadByte(msg_t *a11)
{
	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);

	DWORD* a1 = (DWORD*)a11;

	int v1; // eax
	int v2; // esi
	char v3; // dl
	unsigned __int8 v4; // dl
	signed int result; // eax

	v1 = a1[5];
	v2 = a1[7];
	if (v2 >= v1 + a1[6])
	{
		*a1 = 1;
		result = -1;
	}
	else
	{
		if (v2 < v1)
		{
			if (v2 >= a1[4] || v2 < 0)
				v3 = 0;
			else
				v3 = *(BYTE *)(a1[2] + v2);
		}
		else
		{
			v3 = *(BYTE *)(a1[3] - v1 + v2);
		}

		DWORD bugAddy = ((((BYTE)v2 - curA11) & 0xF) + MSGMap[a11->data].a10);
		if (Utils::ValidAddy(bugAddy))
		{
			DWORD v66 = ((unsigned int)(v2 - curA11) < 0x10) * *(BYTE *)bugAddy;
			
			v4 = v3 - v66;
		}
		else
		{
			v4 = *(unsigned __int8 *)(a1[3] - v1 + v2);
		}
			
		a1[7] = v2 + 1;
		result = v4;
	}


	return result;
}

int hk_MSG_ReadString(msg_t* a11, int a2, unsigned int a3)
{
	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);
	unsigned int i; // edi
	signed int v4; // esi

	for (i = 0; ; ++i)
	{
		v4 = hk_MSG_ReadByte(a11);
		if (v4 == -1)
			v4 = 0;
		if (i < a3)
			*(BYTE *)(i + a2) = I_CleanChar(v4);
		if (!v4)
			break;
	}
	*(BYTE *)(a2 + a3 - 1) = 0;

	if ((DWORD)_ReturnAddress() == 0x624D4B) //SV_ProcessClientCommands
	{
		char* rettt = SV_Process_ClientMessage((char*)a2);
		if (rettt)
			a2 = (int)rettt;
	}

	return a2;
}

DWORD *__cdecl hk_MSG_ReadLong(msg_t *a11)
{
	DWORD retAddy = (DWORD)_ReturnAddress();
	DWORD curA11 = GetA11(retAddy, a11);
	if (retAddy == 0x4B7E02)
	{
		curA11 = a11->readcount;
	}

	DWORD* a1 = (DWORD*)a11;

	DWORD *v1; // esi
	int v2; // eax
	int v3; // edi
	int v4; // ecx
	DWORD *v5; // eax
	DWORD *result; // eax
	
	v1 = a1;
	v2 = a1[5] + a1[6];
	v3 = a1[7];
	if (v3 + 4 > v2)
	{
		*a1 = 1;
		result = (DWORD *)-1;
	}
	else
	{
		_asm pushad;
		_asm mov eax, v2;
		SomeMSGClamp((int)a1, v3, (int)&a1, 4);
		_asm popad;

		DWORD bugAddy = ((((BYTE)v3 - curA11) & 0xC) + MSGMap[a11->data].a10);
		if (Utils::ValidAddy(bugAddy))
		{
			v4 = *(DWORD *)bugAddy * ((unsigned int)(v3 - curA11) < 0x10);
			v5 = a1;
			result = (DWORD *)((char *)v5 - v4);
		}
		else
		{
			result = a1;
		}
		
		v1[7] = v3 + 4;
		
	}

	if (retAddy == 0x4B7DF6)
	{
		MSGMap[a11->data].a10 = (DWORD)Scr_GetScrambleBuf((DWORD)result);
		MSGMap[a11->data].a11 = (DWORD)a11->readcount;
	}
	return result;
}


void __cdecl hk_MSG_SetDefaultUserCmd(int a1, DWORD *a2)
{
	int v2; // edi
	DWORD *v3; // edx
	float *v4; // eax
	signed int v5; // esi
	int v6; // eax
	float v7; // [esp+Ch] [ebp+4h]

	*a2 = 0;
	a2[1] = 0;
	a2[2] = 0;
	a2[3] = 0;
	a2[4] = 0;
	a2[5] = 0;
	a2[6] = 0;
	a2[7] = 0;
	a2[8] = 0;
	a2[9] = 0;

	v2 = a1;
	*((WORD *)a2 + 10) = *(WORD *)(a1 + 692);
	*((WORD *)a2 + 12) = *(WORD *)(a1 + 680);
	v3 = a2 + 2;
	v4 = (float *)(a1 + 96);
	v5 = 2;

	do
	{
		v7 = (v4[43] - *v4) * *(double*)0x731220 + *(double*)0x7139D0;
		*v3 = (unsigned __int16)(signed int)(v7 - 0.4999999990686774);
		++v4;
		++v3;
		--v5;
	} while (v5);

	if (*(DWORD *)(v2 + 16) & 0x1000)
	{
		v6 = *(DWORD *)(v2 + 176);
		if (v6 & 8)
		{
			a2[1] |= 0x100u;
		}
		else if (v6 & 4)
		{
			a2[1] |= 0x200u;
		}
		if (0.0 != *(float *)(v2 + 704))
			a2[1] |= 0x800u;
	}
}

int __cdecl hk_MSG_ReadStringLine(msg_t *a11, int a2, unsigned int a3)
{
	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a11);
	unsigned int i; // edi
	signed int v4; // eax
	signed int v5; // esi

	for (i = 0; ; ++i)
	{
		v4 = hk_MSG_ReadByte(a11);
		v5 = v4;
		if (v4 == 37)
		{
			v5 = 46;
		}
		else if (v4 == 10 || v4 == -1)
		{
			v5 = 0;
		}
		if (i < a3)
			*(BYTE *)(i + a2) = I_CleanChar(v5);
		if (!v5)
			break;
	}
	*(BYTE *)(a2 + a3 - 1) = 0;
	return a2;
}

int* hk_MSG_BeginReading(msg_t* msgg)
{
	DWORD* msg = (DWORD*)msgg;
	int* ret = (int*)oMSG_BeginReading(msgg);
	MSGMap[msgg->data].a10 = (int)ScrambleBuf;
	MSGMap[msgg->data].a11 = 0xFF;
	return ret;
}

DWORD* ECM_CLIENT = 0;
void hk_SV_ExecuteClientMessage(DWORD* client, DWORD *a2)
{
	ECM_CLIENT = client;

	oSV_ExecuteClientMessage(client, a2);
}

std::vector<char*> dat;
int* __cdecl hk_MSG_Init(msg_t *msgg, int a2, int a3)
{
	DWORD* msg = (DWORD*)msgg;
	int* ret = (int*)oMSG_Init(msgg, a2, a3);

	MSGMap[msgg->data].a10 = (int)ScrambleBuf;
	MSGMap[msgg->data].a11 = 0xFF;
	MSGMap[msgg->data].curTick = GetTickCount();

	DWORD retAddy = (DWORD)_ReturnAddress();

	if (retAddy == 0x4817E5) 
	{
		MSGMap[msgg->data].a10 = (DWORD)Scr_GetScrambleBuf(*(int*)0xA25270);
	}
	else if (retAddy == 0x4F2AB7)
	{
		if (ECM_CLIENT)
		{
			MSGMap[msgg->data].a10 = (DWORD)Scr_GetScrambleBuf(ECM_CLIENT[0x839A] + ((ECM_CLIENT[0x8398]) << 8));
		}	
	}

	return ret;
}


DWORD oldTickCheck = 0;
int hk_MSG_Discard(msg_t* a1)
{
	auto rr = MSGMap.find(a1->data);
	if (rr != MSGMap.end())
		MSGMap.erase(rr);


	DWORD curTickCheck = GetTickCount();
	int seconds = (curTickCheck - oldTickCheck) / 1000;

	if (abs(seconds) >= 10)
	{
		auto i = MSGMap.begin();
		while (i != MSGMap.end())
		{
			DWORD cTick = i->second.curTick;
			int cSeconds = (curTickCheck - cTick) / 1000;
			if (abs(cSeconds) >= 10)
			{
				i = MSGMap.erase(i);
			}
			else
			{
				++i;
			}
		}

		oldTickCheck = curTickCheck;
	}
	

	return oMSG_Discard((int)a1);
}


msg_t* __cdecl hk_sub_4C2920(msg_t* a1, float a2)
{
	float v2; // ST0C_4
	msg_t* result; // eax
	int v4; // edx
	signed int v5; // [esp+14h] [ebp+8h]

	DWORD curA11 = GetA11((DWORD)_ReturnAddress(), a1);

	v2 = a2 * 182.0444488525391 + 0.5;
	v5 = (signed int)(v2 - 0.4999999990686774);
	result = a1;
	v4 = a1->cursize;
	if (v4 + 2 >  a1->maxsize)
	{
		a1->overflowed = 1;
	}
	else
	{
		*(WORD *)(v4 + a1->data) = v5 + *(WORD *)((((BYTE)v4 - curA11) & 0xE) + MSGMap[a1->data].a10) * ((unsigned int)(v4 - curA11) < 0x10);
		a1->cursize = v4 + 2;
	}
	return result;
}

DWORD CL_ParseCommandString_Ret = 0;
DWORD CPS_V1 = 0;
msg_t* CPS_MSG = 0;
__declspec(naked) void CL_ParseCommandString_MHk()
{
	_asm mov CPS_V1, eax;
	_asm mov CPS_MSG, edi;
	_asm pushad;

	MSGMap[CPS_MSG->data].a10 = (DWORD)Scr_GetScrambleBuf(CPS_V1);

	_asm popad;
	_asm jmp CL_ParseCommandString_Ret;
}


DWORD CL_ParseGameState_Ret = 0;
DWORD CPG_V1 = 0;
msg_t* CPG_MSG = 0;
__declspec(naked) void CL_ParseGameState_MHk()
{
	_asm mov CPG_V1, eax;
	_asm mov CPG_MSG, esi;
	_asm pushad;

	MSGMap[CPG_MSG->data].a10 = (DWORD)Scr_GetScrambleBuf(*(int*)0xA25270 + (CPG_V1 << 8));

	_asm popad;
	_asm jmp CL_ParseGameState_Ret;
}


DWORD CL_ParseSnapshot_Ret = 0;
int CSP_V1 = 0;
msg_t* CSP_MSG = 0;

__declspec(naked) void CL_ParseSnapShot_MHk()
{
	//_asm mov CSP_V1, eax; old
	_asm mov CSP_MSG, edi;
	//additional fix
	_asm
	{
		push ecx;
		push edx;

		mov ecx, eax;
		mov eax, 0x51EB851F;
		imul ecx;

		mov CSP_V1, ecx; // backup for [esi+3124h]
		//mov[esi+3124h], ecx will be done on return anyways
		sar edx, 4;
		mov ecx, edx;
		shr ecx, 0x1F;
		add ecx, edx;

		push ecx;
		call Scr_GetScrambleBuf;
		add esp, 4;
		mov ecx, eax; //unscrambled buf backup
		mov eax, CSP_V1; //get backup
		mov CSP_V1, ecx; //set unscrambled buf

		pop edx;
		pop ecx;
	}
	
	//end
	_asm pushad;

	MSGMap[CSP_MSG->data].a10 = CSP_V1;

	_asm popad;
	_asm jmp CL_ParseSnapshot_Ret;
}

DWORD CG_DeployServerCommand_Ret = 0, CDSC_ECX = 0;
void Process_CGDSC()
{
	char* realString = (char*)CDSC_ECX;
	if (!realString)
		return;

	char cc = GSSCMap[realString[0]];
	if (cc >= 0)
		realString[0] = cc;
}

_declspec(naked) void CG_DeployServerCommand_MHk()
{
	_asm mov CDSC_ECX, ecx;
	_asm pushad;
	Process_CGDSC();
	_asm popad;
	_asm jmp CG_DeployServerCommand_Ret;
}


DWORD CL_CGameNeedsServerCommand_Ret = 0, CGNSC_EAX = 0, CGNSC_GBAK_PTR = 0;
char CGNSC_gBak=0;
void Process_CGNSC()
{
	char* realString = (char*)CGNSC_EAX;
	if (!realString)
		CGNSC_GBAK_PTR = CGNSC_EAX;

	char cc = GSSCMap_CGNSC[realString[0]];
	if (cc >= 0)
	{
		CGNSC_gBak = cc;
		CGNSC_GBAK_PTR = (DWORD)(&CGNSC_gBak);
		return;
	}

	CGNSC_GBAK_PTR = CGNSC_EAX;
}

_declspec(naked) void CL_CGameNeedsServerCommand_MHk()
{
	_asm mov CGNSC_EAX, eax;
	_asm pushad;
	Process_CGNSC();
	_asm popad;
	_asm mov eax, CGNSC_GBAK_PTR;
	_asm jmp CL_CGameNeedsServerCommand_Ret;
}

int hk_SV_SendServerCommandInner(DWORD *client, signed int a2, char* message)
{
	if (!message)
		return oSV_SendServerCommandInner(client, a2, message);

	char cc = GSSCMap_Server[message[0]];
	if (cc != 0)
	{
		message[0] = cc;
	}

	return oSV_SendServerCommandInner(client, a2, message);
}

int hk_sub_624560(DWORD* client, msg_t* msg)
{
	oldLongClient = client;
	return osub_624560(client, msg);
}

char backupTokenString[1024];
DWORD* __cdecl hk_Cmd_TokenizeStringNoEval(char* str)
{
	if ((DWORD)_ReturnAddress() == 0x417B16)
	{
		size_t lol = strlen(str);
		if (lol > 1023)
			return oCmd_TokenizeStringNoEval(str);

		memcpy(backupTokenString, str, lol + 1);
		char cc = GSSCMap[backupTokenString[0]];
		if (cc != 0)
		{
			backupTokenString[0] = cc;
			return oCmd_TokenizeStringNoEval(backupTokenString);
		}
	}

	return oCmd_TokenizeStringNoEval(str);
}

int hk_CL_CGameNeedsServerCommand(int a1, int a2)
{
	char* serverCommands = (char*)0xA45280;
	char* str = &serverCommands[1024 * (a2 & 0x7F)];

	char* cmdTokenz = **(char***)0x1B05034;
	char* cmdToken = (char*)cmdTokenz[*(DWORD*)0x1B04FD0];

	int ret = oCL_CGameNeedsServerCommand(a1, a2);

	return ret;
}

int hk_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float angle, const RGBA_COLOR* color, int material)
{
	return oR_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, angle, color, material);
}

DWORD AddCmdDrawStretchPic_Ret = 0, AddCmdDrawStretchPic_ESI = 0;
_declspec(naked) void AddCmdDrawStretchPic_MHk()
{
	_asm mov AddCmdDrawStretchPic_ESI, esi;
	_asm mov    edx, DWORD PTR ds : 0x67428b0;
	_asm mov esi, edx; 
	_asm pushad;
	
	_asm popad;
	_asm jmp AddCmdDrawStretchPic_Ret;
}

DWORD PlayerStateDelta_Ret = 0, RRET = 0;
_declspec(naked) void PlayerstateDelta_MHk()
{
	RRET = (DWORD)_ReturnAddress();
	_asm pushad;
	//printf("RET: 0x%x\n", RRET);
	_asm popad;
	_asm jmp PlayerStateDelta_Ret;
}

typedef signed int(__cdecl* tG_MaterialIndex)(const char *a1);
tG_MaterialIndex oG_MaterialIndex;

signed int __cdecl hk_G_MaterialIndex(const char *a1)
{
	//printf("Precache: %s\n", a1);
	return oG_MaterialIndex(a1);
}

void ClientCommand_hk(int a1)
{
	int sv_cmd_args_nesting = *(int*)0x1B282A0;

	int* sv_cmd_args_argc = (int*)0x1B282E4;
	char** sv_cmd_args_argv = *(char***)0x1B28304;

	int cargc = sv_cmd_args_argc[sv_cmd_args_nesting];

	char *cgcBak = 0, *cgc2Bak = 0;
	if (cargc > 1)
	{
		char* cargv = sv_cmd_args_argv[sv_cmd_args_nesting];
		char* cargv2 = sv_cmd_args_argv[sv_cmd_args_nesting] + 4;

		if (!strcmp(cargv, "n"))
		{
			int acc = atoi(cargv2);
			std::string *gg = &ActionMap_Inverse[acc];
			if (!gg->empty())
			{
				cgcBak = cargv;
				cgc2Bak = cargv2;

				sv_cmd_args_argv[sv_cmd_args_nesting] = (char*)0x716228; // "nt"
				*(char**)(&sv_cmd_args_argv[sv_cmd_args_nesting] + 4) = (char*)gg->c_str(); 

			}
		}
	}
	

	oClientCommand(a1);

	if (cgcBak)
	{
		sv_cmd_args_argv[sv_cmd_args_nesting] = cgcBak;
		*(char**)(&sv_cmd_args_argv[sv_cmd_args_nesting] + 4) = cgc2Bak;
	}
}

char __cdecl hk_MSG_WriteDeltaPlayerState(int a1, msg_t *msg, int a3, char *a4, int a5)
{
	DWORD retAddy = (DWORD)_ReturnAddress();

	if (retAddy == 0x42F1CA || retAddy == 0x42F1A9) //SV_WriteSnapshotToClient
		MSGMap[msg->data].a11 = 0x4;
	else //SV_ArchiveSnapshot
		MSGMap[msg->data].a11 = 0x0;

	return oMSG_WriteDeltaPlayerState(a1, msg, a3, a4, a5);
}

void hk_SV_ExecuteClientCommand(const char *s, int clientOK, int fromOldServer)
{
	oSV_ExecuteClientCommand(s, clientOK, fromOldServer);

	if (oldMSGBuf)
		strcpy(servMSGBuf, oldMSGBuf);
}

typedef void(__cdecl* tMSG_WriteDeltaHudElems)(int a2, msg_t *msg, int* hudelem_from, int* hudelem_to, int count);
tMSG_WriteDeltaHudElems oMSG_WriteDeltaHudElems;

int typeBak = 0;
void hk_MSG_WriteDeltaHudElems(int a2, msg_t *msg, int* hudelem_from, int* hudelem_to, int count)
{
	_asm pushad;

	typeBak = hudelem_to[0];
	hudelem_to[0] = max(1, typeBak - 2);
	_asm popad;

	oMSG_WriteDeltaHudElems(a2, msg, hudelem_from, hudelem_to, count);
}

void PatchServerPackets()
{
	Utils::PatchAddy<byte>(0x418251, 1); // SV_UpdateServerCommandsToClient => CL_ParseCommandString
	Utils::PatchAddy<byte>(0x42F0D3, 0);
	Utils::PatchAddy<byte>(0x46AA43, 5);
	Utils::PatchAddy<byte>(0x46AAA7, 5);
	Utils::PatchAddy<byte>(0x4B38B0, 1); // SV_UpdateServerCommandsToClient => CL_ParseCommandString
	Utils::PatchAddy<byte>(0x5A78DE, 3);
	Utils::PatchAddy<byte>(0x5A7ABB, 5);
	Utils::PatchAddy<byte>(0x5A7AE8, 5);
	Utils::PatchAddy<byte>(0x62456C, 2);
	Utils::PatchAddy<byte>(0x6245B1, 3);
	Utils::PatchAddy<byte>(0x624811, 5);
	Utils::PatchAddy<byte>(0x624849, 5);
}

void PatchGamestate()
{
	Utils::PatchAddy<byte>(0x5AB941, 5); //CL_ParseGameState patch
	Utils::PatchAddy<byte>(0x5AB952, 3); //CL_ParseGameState patch
	Utils::PatchAddy<byte>(0x5ABBFD, 5); //CL_ParseGameState patch
}


void PatchHudElems_Client()
{
	byte patcharray[] = { 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 02, 02 };
	Utils::FillAddy(0x589BF8, 0, 14);
	Utils::PatchAddy(0x589BF8, patcharray, 12);

	Utils::PatchAddy<byte>(0x589AD0, 0x0D);

	DWORD patchhuds2[] = { 0x588DF8, 0x588E47, 0x588D55, 0x588E66, 0x588E17, 0x588E17 , 0x588E17, 0x588E2F, 0x588E2F, 0x588E2F };
	Utils::PatchAddy(0x588F50, (byte*)patchhuds2, sizeof(DWORD) * ARRAYSIZE(patchhuds2));

	Utils::PatchAddy<byte>(0x588404, 0xFB);

	byte patchhuds3[] = { 0x00, 0x00, 0x00 ,0x01, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00 };
	Utils::PatchAddy(0x588754, patchhuds3, 15);
	Utils::PatchAddy<byte>(0x5886FB, 0x0C);

	Utils::PatchAddy(0x5887E4, patchhuds3, 15);
	Utils::PatchAddy<byte>(0x58877B, 0x0C);

	Utils::PatchAddy<byte>(0x484766, 13);
}


void fixHudElem_server(int &type)
{
	if (type >= 6)
		type = max(4, type - 2);
}


char hk_HudElem_UpdateClient_copyfunction(unsigned int a1, char *a2, signed int a3)
{
	if(!a1 || !a2)
		return sub_454310((char*)a1, a2, a3);

	int oldElem = *(int*)a2;
	fixHudElem_server(*(int*)a2);
	char ret = sub_454310((char*)a1, a2, a3);
	*(int*)a2 = oldElem;

	return ret;
}

DWORD GDSC_WepFix_Ret = 0, GDSC_WepFix_RetBack = 0x596056;
__declspec(naked) void GDSC_WepFix_MHk()
{
	_asm
	{
		cmp eax, 0;
		jz wfxhk;
		jmp GDSC_WepFix_Ret;

	wfxhk:
		jmp GDSC_WepFix_RetBack;
	}
}
void callHook(DWORD_PTR target, void* hookFunction)
{
	DWORD oldProt, oldProt2;

	VirtualProtect((void*)target, 5, PAGE_EXECUTE_READWRITE, &oldProt);

	*(byte*)target = 0xE8;
	*(DWORD*)(target + 1) = ((DWORD)hookFunction - target - 5);


	VirtualProtect((void*)target, 5, oldProt, &oldProt2);
}

void PatchHudElems_Server()
{
	callHook(0x492C4E, hk_HudElem_UpdateClient_copyfunction);
	callHook(0x492C76, hk_HudElem_UpdateClient_copyfunction);
}

void LoadProgramBuf()
{
	ProgramBuf = (char*)ResourceLoader::loadResource(IDR_BINARY2, "Binary");
}

/// ***********************

DWORD SV_ConnectionLessPacket_Ret = 0;
msg_t* SV_ConnectionLessPacket_msg = 0;

void SV_ConnectionLessPacket_Call()
{
	if(SV_ConnectionLessPacket_msg)
		MSGMap[SV_ConnectionLessPacket_msg->data].a11 = 0xFF;
}

__declspec(naked) void SV_ConnectionLessPacket_MHk()
{
	_asm
	{
		mov SV_ConnectionLessPacket_msg, esi;
		pushad;
		call SV_ConnectionLessPacket_Call;
		popad;
		jmp SV_ConnectionLessPacket_Ret;
	}
}

void MSGHooks::Hook()
{
	/// ***********************
	SV_ConnectionLessPacket_Ret = (DWORD)DetourFunction((PBYTE)0x625790, (PBYTE)SV_ConnectionLessPacket_MHk);
	/// ***********************


	LoadProgramBuf();
	LoadA11();
	LoadGSSCMap();
	LoadActionMap();

	memset(ScrambleBuf, 0, 0x620B);

	byte targarray[] = { 0x00 ,0x00 ,0x03 ,0x01 ,0x03 ,0x03 ,0x03 ,0x03 ,0x03 ,0x03 ,0x03 ,0x00 ,0x00 ,0x00 ,0x00 ,0x03 ,0x00 ,0x03 ,0x02 ,0x03 ,0x03 ,0x03 ,0x03 ,0x03 ,0x00 ,0x00 };
	Utils::PatchAddy(0x6256E4, targarray, 26);

	Utils::PatchAddy<byte>(0x481842, 5); //make max packet from 6 to 5
	Utils::PatchAddy(SendServerMessage_SwitchAddy, (byte*)CL_SendServerMessageSwitches, sizeof(DWORD) * 5);

	//Do the same for Server functions
	PatchServerPackets();

	PatchGamestate();
	Utils::NOPAddy(0x59C0AF, 5);  //Mute vision warnings
	Utils::NOPAddy(0x4EBC24, 16); //Mute playlist warnings

	PatchHudElems_Client(); 
	PatchHudElems_Server();

	oMSG_Init = (tMSG_Init)DetourFunction((PBYTE)0x4351C0, (PBYTE)hk_MSG_Init);
	oMSG_ReadString = (tMSG_ReadString)DetourFunction((PBYTE)0x493460, (PBYTE)hk_MSG_ReadString);
	oMSG_ReadByte = (tMSG_ReadByte)DetourFunction((PBYTE)0x426E70, (PBYTE)hk_MSG_ReadByte);
	oMSG_ReadLong = (tMSG_ReadLong)DetourFunction((PBYTE)0x60E250, (PBYTE)hk_MSG_ReadLong);
	oMSG_ReadShort = (tMSG_ReadShort)DetourFunction((PBYTE)0x49E580, (PBYTE)hk_MSG_ReadShort);
	oMSG_ReadStringLine = (tMSG_ReadStringLine)DetourFunction((PBYTE)0x491E70, (PBYTE)hk_MSG_ReadStringLine);

	oMSG_WriteByte = (tMSG_WriteByte)DetourFunction((PBYTE)0x469B60, (PBYTE)hk_MSG_WriteByte);
	oMSG_WriteShort = (tMSG_WriteShort)DetourFunction((PBYTE)0x504510, (PBYTE)hk_MSG_WriteShort);
	oMSG_WriteString = (tMSG_WriteString)DetourFunction((PBYTE)0x4D9030, (PBYTE)hk_MSG_WriteString);
	oMSG_WriteLong = (tMSG_WriteLong)DetourFunction((PBYTE)0x4A7C20, (PBYTE)hk_MSG_WriteLong);

	oMSG_SetDefaultUserCmd =  (tMSG_SetDefaultUserCmd)DetourFunction((PBYTE)0x42D760, (PBYTE)hk_MSG_SetDefaultUserCmd);
	oMSG_Discard = (tMSG_Discard)DetourFunction((PBYTE)0x4AB4B0, (PBYTE)hk_MSG_Discard);
	
	oMSG_WriteDeltaPlayerState = (tMSG_WriteDeltaPlayerState)DetourFunction((PBYTE)0x4150D0, (PBYTE)hk_MSG_WriteDeltaPlayerState);
	
	osub_4C2920 = (tsub_4C2920)DetourFunction((PBYTE)0x4C2920, (PBYTE)hk_sub_4C2920);
	osub_624560 = (tsub_624560)DetourFunction((PBYTE)0x624560, (PBYTE)hk_sub_624560);

	CL_ParseCommandString_Ret = (DWORD)DetourFunction((PBYTE)0x5ABD6D, (PBYTE)CL_ParseCommandString_MHk);
	CL_ParseGameState_Ret = (DWORD)DetourFunction((PBYTE)0x5AB882, (PBYTE)CL_ParseGameState_MHk);
	CL_ParseSnapshot_Ret = (DWORD)DetourFunction((PBYTE)0x5AB371, (PBYTE)CL_ParseSnapShot_MHk);

	oSV_ExecuteClientMessage = (tSV_ExecuteClientMessage)DetourFunction((PBYTE)0x4F2A80, (PBYTE)hk_SV_ExecuteClientMessage);

	oSV_SendServerCommandInner = (tSV_SendServerCommandInner)DetourFunction((PBYTE)0x45C050, (PBYTE)hk_SV_SendServerCommandInner);
	oCL_CGameNeedsServerCommand = (tCL_CGameNeedsServerCommand)DetourFunction((PBYTE)0x417A70, (PBYTE)hk_CL_CGameNeedsServerCommand);
	oCmd_TokenizeStringNoEval = (tCmd_TokenizeStringNoEval)DetourFunction((PBYTE)0x446CE0, (PBYTE)hk_Cmd_TokenizeStringNoEval);

	oSV_ExecuteClientCommand = (tSV_ExecuteClientCommand)DetourFunction((PBYTE)0x624C40, (PBYTE)hk_SV_ExecuteClientCommand);
	
	GDSC_WepFix_Ret = (DWORD)DetourFunction((PBYTE)0x595C65, (PBYTE)GDSC_WepFix_MHk);	
}