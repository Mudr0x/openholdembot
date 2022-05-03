#pragma once
//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose:
//
//******************************************************************************

#ifdef OPENTRACKER_DLL_EXPORTS
#define OTDLL_API_QUERYDEFS extern "C" __declspec(dllexport)
#else
#define OTDLL_API_QUERYDEFS extern "C" __declspec(dllimport)
#endif



// OpenTracker DB Management
OTDLL_API_QUERYDEFS	CString OT_DLL_GetDBQuery(CString db_queryname, CString dbname, CString db_username);


// OpenTracker Stats Management
OTDLL_API_QUERYDEFS	int			OT_DLL_GetNumberOfStats();
OTDLL_API_QUERYDEFS	CString		OT_DLL_GetDescription(int stats_index);
OTDLL_API_QUERYDEFS	CString		OT_DLL_GetBasicSymbolNameWithoutPTPrefix(int stats_index);
OTDLL_API_QUERYDEFS	bool		OT_DLL_IsBasicStat(int stats_index);
OTDLL_API_QUERYDEFS	bool		OT_DLL_IsPositionalPreflopStat(int stats_index);
OTDLL_API_QUERYDEFS	bool		OT_DLL_IsAdvancedStat(int stats_index);
OTDLL_API_QUERYDEFS	double		OT_DLL_GetStat(CString symbol_name, int chair);
OTDLL_API_QUERYDEFS	void		OT_DLL_SetStat(int stats_index, int chair, double value);
OTDLL_API_QUERYDEFS	bool		OT_DLL_IsValidSymbol(CString symbol_name);
OTDLL_API_QUERYDEFS	void		OT_DLL_ClearPlayerStats(int chair);
OTDLL_API_QUERYDEFS	void		OT_DLL_ClearAllPlayerStats();
OTDLL_API_QUERYDEFS	CString		OT_DLL_GetStatQuery(int stats_index,
												bool isomaha, bool istournament,
												int site_id, CString player_name,
												double big_blind);