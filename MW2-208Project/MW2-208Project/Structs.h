#pragma once

typedef unsigned char byte;

struct dvar_t_211
{
	char pad[0x0C];
	union
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		char* string;
		float value;
		float vector[4];
		float color[4];
	} current;
};

struct dvar_t
{
	char pad[16];
	union
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		char* string;
		float value;
		float vector[4];
		float color[4];
	} current;
};

struct directory_t
{
	char path[256];
	char gamedir[256];
};

struct iwd_t
{
	char iwdFilename[256];
	char iwdBasename[256];
	char iwdGamename[256];
	int handle;
	int checksum;
	int pure_checksum;
	int hasOpenFile;
	int numFiles;
	int referenced;
	int hashSize;
	int hashTable;
	int buildBuffer;
};

struct searchpath_s
{
	searchpath_s* next;
	iwd_t* iwd;
	directory_t* dir;
	int bLocalized;
	int ignore;
	int ignorePureCheck;
	int language;
};

struct msg_t
{
	int overflowed;
	int readOnly;
	char* data;
	int splitData;
	int maxsize;
	int cursize;
	int splitSize;
	int readcount;
	int bit;
	int lastEntityRef;
	int a10;
	int a11;
};

class RGBA_COLOR
{
public:
	float r, g, b, a;
	const static RGBA_COLOR	transparentRed;
	const static RGBA_COLOR	transparentYellow;
	const static RGBA_COLOR	transparentOrange;
	const static RGBA_COLOR	transparentPink;
	const static RGBA_COLOR	colRed;
	const static RGBA_COLOR	colCyan;
	const static RGBA_COLOR	colWhite;
	const static RGBA_COLOR	versionColor;
	const static RGBA_COLOR	consoleColor;
	const static RGBA_COLOR	transparentWhite;
	const static RGBA_COLOR	colBlack;
	const static RGBA_COLOR    colYellow;
	const static RGBA_COLOR	colBlue;
	const static RGBA_COLOR	transparentBlack;
	const static RGBA_COLOR	transparentGreen;
	const static RGBA_COLOR	colGreen;
	const static RGBA_COLOR    radarLine;
	const static RGBA_COLOR    colSHADER;
};


enum netadrtype_t {
	NA_BOT = 0x0,
	NA_BAD = 0x1,
	NA_LOOPBACK = 0x2,
	NA_BROADCAST = 0x3,
	NA_IP = 0x4,
};

struct netadr_t {
	netadrtype_t type;
	union {
		uint8_t ip[4];
		uint8_t ipx[8];
	};
	uint16_t port;
	int32_t addrHandleIndex;

};

enum netsrc_t {
	NS_CLIENT = 0x0,
	NS_SERVER = 0x1,
};

struct netProfilePacket_t {
	int iTime;
	int iSize;
	int bFragment;
};

struct netProfileStream_t {
	netProfilePacket_t packets[60];
	int iCurrPacket;
	int iBytesPerSecond;
	int iLastBPSCalcTime;
	int iCountedPackets;
	int iCountedFragments;
	int iFragmentPercentage;
	int iLargestPacket;
	int iSmallestPacket;
};

struct netProfileInfo_t {
	netProfileStream_t send;
	netProfileStream_t recieve;
};

struct netchan_t {
	int outgoingSequence;
	netsrc_t sock;
	int dropped;
	int incomingSequence;
	netadr_t remoteAddress;
	int fragmentSequence;
	int fragmentLength;
	char* fragmentBuffer;
	int fragmentBufferSize;
	int unsentFragments;
	int unsentFragmentStart;
	int unsentLength;
	char* unsentBuffer;
	int unsentBufferSize;
	netProfileInfo_t prof;
};

enum UPNP_NatType {
	NAT_UNKNOWN = 0x0,
	NAT_OPEN = 0x1,
	NAT_MODERATE = 0x2,
	NAT_STRICT = 0x3,
};

struct PartyClient {
	char pad_0x0000[0x18]; //0x0000
	char clientStatus; //0x0018
	char pad_0x0019[0x1]; //0x0019
	char name[32]; //0x687888
	char pad_0x003A[0x1E]; //0x003A
	uint8_t localIp[4]; //0x0058
	uint8_t remoteIp[4]; //0x005C
	char pad_0x0060[0x34]; //0x0060
	int level; //0x0094
	int prestige; //0x0098
	char pad_0x009C[0x2C]; //0x009C
	__int64 steamId; //0x00C8
	char pad_0x00D0[0x10]; //0x00D0

};
#pragma pack()

class RegisteredUser {
public:
	char active; //0x0000
	char pad_0x0001[0x7]; //0x0001
	uint64_t xuid; //0x0008
	int N00010F2B; //0x0010
	int N00010F2C; //0x0014

}; //Size=0x0018


struct SessionData_s {
	char* sessionName; //0x0000
	char pad_0x0004[0x1C]; //0x0004
	int numRegisteredUsers; //0x0020
	char pad_0x0024[0x4]; //0x0024
	RegisteredUser registeredUsers[18]; //0x0028
	int N00010F55; //0x01D8
	int N00010F8A; //0x01DC
	int N00010F56; //0x01E0
	int N00010F57; //0x01E4
	int N00010F81; //0x01E8
	char pad_0x01EC[0x38]; //0x01EC
	int publicSlots; //0x0224
	int flags; //0x0228
	char pad_0x022C[0xC]; //0x022C
	__int64 steamId; //0x0238
	int partyListSlot; //0x0240
	netadr_t addr; //0x0244
	char pad_0x024E[0x1]; //0x024E
};

#pragma pack(1)
struct PartyData_s {
	SessionData_s* gameSession; //0x0000
	char pad_0x0004[0x4]; //0x0004
	SessionData_s* presenceSession; //0x0008
	char pad_0x000C[0xD4]; //0x000C
	PartyClient partyMembers[24]; //0x00E0
	char pad_0x15E0[0x1EC]; //0x15E0
	uint32_t startTime; //0x17CC
	char pad_0x17D0[0x20]; //0x17D0
	int bSomePartyFlag; //0x17F0
	char pad_0x17F4[0x8]; //0x17F4
	int partyActive; //0x17FC
	int areWeHost; //0x1800
	char pad_0x1804[0xBC8]; //0x1804
	int mapIndex; //0x23CC
	char pad_0x23D0[0x4]; //0x23D0
	PartyData_s* partyToNotify; //0x23D4
	char pad_0x23D8[0x420]; //0x23D8
};