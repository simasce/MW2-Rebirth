#include "stdafx.h"

void DvarManager::init()
{
	if (!rebirth_bypassvac)
		rebirth_bypassvac = Engine->Dvar_RegisterBool("rebirth_bypassvac", 0, 0, "Enables VAC bypass.");

	if (!rebirth_mod)
		rebirth_mod = Engine->Dvar_RegisterString("rebirth_mod", (char*)0x6DECEA, 0, "Sets the mod. Empty string disables mod load.");

	if (!rebirth_openNat)
		rebirth_openNat = Engine->Dvar_RegisterBool("rebirth_openNat", 0, 0, "Forces open NAT.");

	if (!rebirth_bounce)
		rebirth_bounce = Engine->Dvar_RegisterBool("rebirth_bounce", 0, 0, "Enables bounce patch.");

	if (!party_connectToOthers)
		party_connectToOthers = Engine->FindDvar("party_connectToOthers");

	if (!protocol)
		protocol = Engine->FindDvar("protocol");

	if (!party_maxplayers)
		party_maxplayers = Engine->FindDvar("party_maxplayers");

	if(!cl_ingame)
		cl_ingame = Engine->FindDvar("cl_ingame");

	if (!party_connectTimeout)
		party_connectTimeout = Engine->FindDvar("party_connectTimeout");

	if (!party_maxTeamDiff)
		party_maxTeamDiff = Engine->FindDvar("party_maxTeamDiff");

	if (!bandwidthtest_enable)
		bandwidthtest_enable = Engine->FindDvar("bandwidthtest_enable");

	if (!migration_dvarerrors)
		migration_dvarerrors = Engine->FindDvar("migration_dvarerrors");

	if (!party_autoTeams)
		party_autoTeams = Engine->FindDvar("party_autoTeams");
}

DvarManager::DvarManager()
{
	init();
}

void DvarManager::update()
{
	init();

	if (rebirth_openNat->current.enabled)
		*(DWORD*)0x79E938 = 1; //Open NAT

	if (!migration_dvarerrors)
		migration_dvarerrors = Engine->FindDvar("migration_dvarErrors");
	else
		migration_dvarerrors->current.enabled = false;


	protocol->current.integer = 149;

	if (!vid_xpos)
		vid_xpos = Engine->FindDvar("vid_xpos");
	else if (r_noborder)
	{
		if (r_noborder->current.enabled && vid_xpos->current.integer != 0)
			vid_xpos->current.integer = 0;
	}

	if (!vid_ypos)
		vid_ypos = Engine->FindDvar("vid_ypos");
	else if (r_noborder)
	{
		if (r_noborder->current.enabled && vid_ypos->current.integer != 0)
			vid_ypos->current.integer = 0;
	}

	static bool oldBounce = rebirth_bounce->current.enabled;
	//Bounce patch
	if (oldBounce != rebirth_bounce->current.enabled)
	{
		if (rebirth_bounce->current.enabled)
		{
			Utils::NOPAddy(0x4F4AD2, 2);
		}
		else
		{
			Utils::PatchAddy<byte>(0x4F4AD2, 0x75);
			Utils::PatchAddy<byte>(0x4F4AD3, 0x14);
		}
		oldBounce = rebirth_bounce->current.enabled;
	}

	static bool oldVac = rebirth_bypassvac->current.enabled;

	if (oldVac != rebirth_bypassvac->current.enabled)
	{
		oldVac = rebirth_bypassvac->current.enabled;
		if (oldVac)
			Utils::BypassVacBan();
		else
			Utils::RemoveVacBanBypass();
	}
}

bool DvarManager::isInGame()
{
	return cl_ingame->current.enabled;
}

void DvarManager::flipConnectToOthers()
{
	party_connectToOthers->current.enabled = !party_connectToOthers->current.enabled;
}

#define G_LOBBYDATA 0x1088E50
#define PARTYSESSION_P 0x6716D68
void DvarManager::forceHost()
{
	static dvar_t* party_autoteams = Engine->FindDvar("party_autoteams");
	static dvar_t* party_minplayers = Engine->FindDvar("party_minplayers");
	static auto party_teamBased = Engine->FindDvar("party_teambased");
	static auto xblive_privatematch = Engine->FindDvar("xblive_privatematch");
	static auto onlinegame = Engine->FindDvar("onlinegame");
	static auto ui_gametype = Engine->FindDvar("ui_gametype");
	static dvar_t* party_maxTeamDiff = Engine->FindDvar("party_maxTeamDiff");
	party_autoteams->current.enabled = false;
	party_maxTeamDiff->current.integer = 0;
	*(DWORD*)0x79E938 = 1; //Open NAT

	std::string gamemode = std::string(ui_gametype->current.string);
	party_teamBased->current.enabled = (gamemode != "dm");
	party_minplayers->current.integer = 1;
	xblive_privatematch->current.enabled = true;
	Engine->BalanceTeams(reinterpret_cast<void*>(G_LOBBYDATA));
	Engine->BalanceTeams(reinterpret_cast<void*>(PARTYSESSION_P));
	Engine->PartyHost_StartMatch(reinterpret_cast<void*>(G_LOBBYDATA), 0);

	xblive_privatematch->current.enabled = false;

	if (party_connectToOthers)
		party_connectToOthers->current.enabled = true;
}
