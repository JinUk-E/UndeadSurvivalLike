#pragma once


// C++ Standard Library
#include <windows.h>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <functional>

#include "Types.h"
#include "Utils.h"
#include "Values.h"
#include "Enums.h"
#include "Defines.h"

#include <format>
#include <filesystem>
namespace fs = std::filesystem;

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma comment(lib, "msimg32.lib")

//»ç¿îµå
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
