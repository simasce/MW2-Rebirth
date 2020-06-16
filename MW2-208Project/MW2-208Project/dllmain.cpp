// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

typedef void(__cdecl* tAddCmdDrawText)(const char *text, int maxChars, void *Font_s, float x, float y, float xScale, float yScale, float rotation, const void* color, int style);
tAddCmdDrawText oAddCmdDrawText;

HWND *ConsoleWindow = (HWND*)0x6503740;

IW4Engine* Engine = nullptr;
DvarManager* Dvars = nullptr;

DWORD_PTR DeadCrashes[] = { 0x4658D0, 0x47BC60 ,0x4AFFF0 ,0x4F2A30 ,0x47A550 ,0x4070F0 ,0x471C50 ,0x4F1650, 0x441BB0, 0x4AE3F0 };

const char* OriginalString = "^1MW2-Rebirth (^3%s.%i^1)";
char VersionText[256];

const char* FullVersion_211 = "Tue Aug 18 14:00:02 2015";
const char* FullVersion_211String = "211";

void updateVersionText()
{
	static int omodLen = strlen(Dvars->rebirth_mod->current.string);
	if (strlen(Dvars->rebirth_mod->current.string) == 0)
	{
		strcpy((char*)VersionText, OriginalString);
		return;
	}
	
	int modLen = strlen(Dvars->rebirth_mod->current.string);

	if (omodLen == modLen)
		return;
	
	memset(VersionText, 0, 256);
	sprintf(VersionText, "%s [Mod: %s]", OriginalString, Dvars->rebirth_mod->current.string);
	omodLen = modLen;
}

bool checkKeyState(DWORD key, int flag)
{
	clock_t	c = clock();
	static BYTE			btKeyState[0x100] = { 0 };	
	static clock_t		clockKeyState[0x100] = { c };

	bool	r = false;
	BYTE	btState = (GetKeyState(key) & 0x8000U) >> 0xF;
	short	wDelay = btKeyState[key] & 2 ? 0x50 : 0x200;

	if (btState)
	{
		if (flag & 1)
		{
			if (!(btKeyState[key] & 1) || c - clockKeyState[key] > wDelay)
			{
				if ((btKeyState[key] & 3) == 1)
					btKeyState[key] |= 2;
				r = true;
				clockKeyState[key] = c;
			}
		}
		else
			r = true;
	}
	else
		btKeyState[key] &= ~(2);
	btKeyState[key] ^= (-btState ^ btKeyState[key]) & 1;
	return r;
}

int SendExecuteCommand(std::string cmd)
{
	size_t scPos, len;
	char tmp[50];
	std::string cmdToSend;
	int i = 0;
	do
	{
		cmd.begin();
		scPos = cmd.find(';');
		if (scPos != std::string::npos)
		{
			len = cmd.copy(tmp, int(scPos), 0);
			tmp[len] = '\0';
			cmdToSend = tmp;
			cmdToSend += '\n';
			Engine->ExecuteSingleCommand(0, 0, cmdToSend.c_str());
			cmd.erase(0, int(scPos) + 1);
		}
		else
		{
			cmd += '\n';
			Engine->ExecuteSingleCommand(0, 0, cmd.c_str());
		}
	} while (scPos != std::string::npos);
	return 0;
}


void GameLoop()
{
	if (!*ConsoleWindow)
		Engine->CreateConsole();

	Dvars->update();

	if (!Dvars->isInGame())
	{
		updateVersionText();
		if (checkKeyState(VK_F9, 1))
			Dvars->forceHost();
		else if (checkKeyState(VK_F10, 1))
			Engine->UI_OpenMenu(0, "popup_gamesetup");
		else if (checkKeyState(VK_F11, 1))
			Dvars->flipConnectToOthers();
	}
}

void hk_AddCmdDrawText(const char *text, int maxChars, void *Font_s, float x, float y, float xScale, float yScale, float rotation, const void* color, int style)
{
	GameLoop();
	return oAddCmdDrawText(text, maxChars, Font_s, x, y, xScale, yScale, rotation, color, style);
}

/*typedef bool(__cdecl *tSteam_IsInValidLobby)(int, int);
tSteam_IsInValidLobby oIsInValidLobby;

bool hk_Steam_IsInValidLobby(int unk, int unk1) 
{
	if (Dvars->rebirth_bypassvac->current.enabled)
		return true;

	return oIsInValidLobby(unk, unk1);
}

using tPartyHost_Frame = int(__cdecl*)(PartyData_s*, int, int);
tPartyHost_Frame oPartyHostFrame;

int PartyHost_Frame_Hook(PartyData_s * party, const int localControllerIndex, const int localClientNum) {

	PartyData_t * g_lobbyData = (PartyData_t*)0x1088E50, *g_partyData = (PartyData_t*)0x1085688;
	IWSteamClient * g_steamClient = *(IWSteamClient**)0x672A90C;

	//if (Dvars->rebirth_bypassvac->current.enabled)
		//g_lobbyData->steamID = g_partyData->steamID = g_steamClient->steamID = g_steamClient->steamID_1 = qwSteamID;

	return oPartyHostFrame(party, localControllerIndex, localClientNum);
}*/


bool Hook208()
{
	if (Utils::ReadAddy<byte>(0x431111) != 208) //GetVersion
		return false; //is not 208

	Engine = new IW4Engine();
	Dvars = new DvarManager();

	//DEADCRASH patch: Obsolete - already done in loader
	for (int i = 0; i < ARRAYSIZE(DeadCrashes); i++)
		Utils::PatchAddy<byte>(DeadCrashes[i] + 5, 0xEB);

	updateVersionText();

	Utils::PatchAddy<byte>(0x647A84, 0xEB); // dvar write protection bypass
	Utils::PatchAddy<byte>(0x647AE5, 0xEB); // dvar cheat protection bypass

	Utils::PatchAddy<byte>(0x4F3021, 149); //GetProtocolVersion

	//dvar - protocol
	Utils::PatchAddy<byte>(0x466D29, 149);
	Utils::PatchAddy<byte>(0x466D2E, 149);
	Utils::PatchAddy<byte>(0x466D33, 149);
	
	Utils::PatchAddy<byte>(0x431111, 211); //GetVersion
	
	Utils::PatchAddy<DWORD>(0x49EBB1, (DWORD)FullVersion_211); //GetFullVersion (Big string)
	Utils::PatchAddy<DWORD>(0x49EBB6, (DWORD)FullVersion_211String); //GetFullVersion "211"
	Utils::PatchAddy<DWORD>(0x4D8A8B, (DWORD)VersionText);

	//Patch steamauth
	byte steamAuthPatch[] = {0xC3, 0x90, 0x90};
	Utils::PatchAddy(0x434EC0, steamAuthPatch, 3);
	byte steamAuthSize[] = { 0x90, 0x67, 0x0A, 0x00 };
	Utils::PatchAddy(0x434FD6, steamAuthSize, 4);

	oAddCmdDrawText = (tAddCmdDrawText)DetourFunction((PBYTE)0x50AC40, (PBYTE)hk_AddCmdDrawText);
	//oIsInValidLobby = (tSteam_IsInValidLobby)DetourFunction((PBYTE)0x471DE0, (PBYTE)hk_Steam_IsInValidLobby);

	MSGHooks::Hook();
	RCEFixes::Init();
	IWDHooks::Hook();
	NoBorderPatch::Hook();

	return true;
}

DWORD WINAPI StartThread(LPVOID lParam)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	if (!Hook208())
	{
		MessageBoxA(0, "Please inject into a valid MW2 208 executable!", "Error", MB_OK | MB_ICONERROR);
		FreeConsole();
		FreeLibraryAndExitThread(ResourceLoader::mainmod, 0);
	}

	FreeConsole();
	ExitThread(0);
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		Utils::Init(hModule);
		ResourceLoader::mainmod = hModule;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartThread, 0, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

