#pragma once

class IW4Engine
{
public:
	IW4Engine();
	~IW4Engine();

	typedef int(__cdecl* tCom_DecompressWithZLib)(DWORD *a1, int *a2, int a3, int *a4);
	tCom_DecompressWithZLib Com_DecompressWithZLib = (tCom_DecompressWithZLib)0x4AABE0;

	typedef void(__cdecl* tPartyHost_StartMatch)(void *PartyData_s_party, int localControllerIndex);
	tPartyHost_StartMatch PartyHost_StartMatch = (tPartyHost_StartMatch)0x41E660;

	typedef void(__cdecl* tBalanceTeams)(void *PartyData_s_party);
	tBalanceTeams BalanceTeams = (tBalanceTeams)0x4EEE30;

	typedef void(__cdecl* tUI_OpenMenu)(int localClientNum, const char *menuName);
	tUI_OpenMenu UI_OpenMenu = (tUI_OpenMenu)0x42DB50;

	typedef void(__cdecl* tCreateConsole)();
	tCreateConsole CreateConsole = (tCreateConsole)0x4D3120;

	typedef dvar_t*(__cdecl* tFindDvar)(char* dvarName);
	tFindDvar FindDvar = (tFindDvar)0x449E20;

	typedef dvar_t*(__cdecl* tDvar_RegisterString)(char* dvarName, char* value, int flags, char* description);
	tDvar_RegisterString Dvar_RegisterString = (tDvar_RegisterString)0x440300;

	typedef dvar_t*(__cdecl* tDvar_RegisterBool)(const char *dvarName, bool value, unsigned int flags, const char *description);
	tDvar_RegisterBool Dvar_RegisterBool = (tDvar_RegisterBool)0x4068E0;

	typedef dvar_t* (__cdecl* tDvar_RegisterInt)(const char *dvarName, int curValue, int minValue, int naxValue, int flags, const char* description);
	tDvar_RegisterInt Dvar_RegisterInt = (tDvar_RegisterInt)0x48DA10;

	typedef void(__cdecl* tExecuteSingleCommand)(int localClientNum, int delay, const char *text);
	tExecuteSingleCommand ExecuteSingleCommand = (tExecuteSingleCommand)0x4393E0;
};

extern IW4Engine *Engine;
