#pragma once
//#include<Config.hpp>
#include <Preprocessor.hpp>

constexpr int Dim = 3;
constexpr int g_MaxLevel = 10;
//g_MaxLevel_modified accounts the initial mesh size as well
//We need to come with better design later
constexpr int g_MaxLevel_modified = g_MaxLevel+3;
constexpr int g_BitsetCoordDataSize = g_MaxLevel_modified;
constexpr int g_BitsetLevelDataSize = LOG2<g_MaxLevel_modified> +1;
constexpr int g_BitsetHashSize = g_MaxLevel_modified * 3 + g_BitsetLevelDataSize;