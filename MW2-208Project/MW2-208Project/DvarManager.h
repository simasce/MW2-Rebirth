#pragma once

class DvarManager
{
private:
	dvar_t* protocol = nullptr;
	dvar_t* party_connectToOthers = nullptr;
	dvar_t* party_connectTimeout = nullptr;
	dvar_t* bandwidthtest_enable = nullptr;
	dvar_t* party_autoTeams = nullptr;
	dvar_t* party_maxTeamDiff = nullptr;
	dvar_t* party_maxplayers = nullptr;
	dvar_t* migration_dvarerrors = nullptr;
	dvar_t* vid_xpos = nullptr;
	dvar_t* vid_ypos = nullptr;	
	dvar_t* cl_ingame = nullptr;

	void init();
public:
	DvarManager();

	void forceHost();
	void update();

	bool isInGame();
	void flipConnectToOthers();

	dvar_t* rebirth_mod = nullptr;
	dvar_t* rebirth_openNat = nullptr;
	dvar_t* rebirth_bounce = nullptr;
};

extern DvarManager* Dvars;