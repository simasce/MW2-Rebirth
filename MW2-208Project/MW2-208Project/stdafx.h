// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>
#include <assert.h>
#include <string>
#include "detours.h"
#include <time.h>
#include <vector>
#include <map>

#include "resource.h"
#include "Patcher.h"
#include "ResourceLoader.h"
#include "Structs.h"
#include "Utils.h"
#include "IW4Engine.h"
#include "DvarManager.h"
#include "NoBorderPatch.h"
#include "MSGHooks.h"
#include "IWDHooks.h"
#include "RCEFixes.h"

using namespace Patcher;