#pragma once

class ResourceLoader
{
public:
	static HMODULE mainmod;
	static LPVOID loadResource(int res, char* type);

};