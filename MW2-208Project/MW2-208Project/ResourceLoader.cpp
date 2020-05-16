#include "stdafx.h"

HMODULE ResourceLoader::mainmod = 0;

LPVOID ResourceLoader::loadResource(int res, char* type)
{
	if (!mainmod)
		return NULL;
	HRSRC b = FindResourceA(mainmod, MAKEINTRESOURCEA(res), type);
	if (b)
	{
		HGLOBAL c = LoadResource(mainmod, b);
		if (c)
		{
			LPVOID lockpic = LockResource(c);
			return lockpic;
		}
	}
	return NULL;
}