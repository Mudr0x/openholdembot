//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: opentracker_query_definitions.cpp : Defines the entry point for the DLL application.
//
//******************************************************************************


#include "stdafx.h"
#include "opentracker_query_definitions.h"

using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "..\Shared\MagicNumbers\MagicNumbers.h"
#include "..\OpenHoldem\NumericalFunctions.h"
#include "OpenTracker_Queries_Version_4.h"



// OpenTracker DB Management /////////////////////

const char* dbschema_filename = "create_db_schema.sql";


//Not exported
CString readFile(const string &fileName)
{
	ifstream file_stream{ fileName };
	CString ErrMsg;

	if (file_stream.fail())
	{
		// Error opening file.
		ErrMsg.Format("Error opening OpenTracker DB schema file.\n Make sure '%s' file is present in your OpenHoldem folder.", dbschema_filename);
		MessageBox(0, ErrMsg, "ERROR", MB_OK);
	}

	ostringstream str_stream{};
	file_stream >> str_stream.rdbuf();  // NOT str_stream << file_stream.rdbuf()

	if (file_stream.fail() && !file_stream.eof())
	{
		// Error reading file.
		ErrMsg.Format("Error reading OpenTracker DB schema file.\n Make sure '%s' file isn't used by another process.", dbschema_filename);
		MessageBox(0, ErrMsg, "ERROR", MB_OK);
	}

	return str_stream.str().c_str();
}

// Not exported
int GetDBQUeryIndex(CString db_queryname) {
	assert(db_queryname != "");
	// This function can (and should) probably be optimized
	// by use of CMaps (binary trees).
	for (int i = 0; i<k_number_of_dbmanagement_queries; ++i) {
		if (db_queryname == db_query_definitions[i].name) {
			return i;
		}
	}
	return kUndefined;
}

OTDLL_API_QUERYDEFS	CString OT_DLL_GetDBQuery(CString db_queryname, CString dbname, CString db_username) {
	int index = GetDBQUeryIndex(db_queryname);
	//AssertRange(index, 0, (k_number_of_dbmanagement_queries - 1));
	CString query;

	// For special case of db schema creation, we handle it on an external sql file (create_db_schema.sql in OH folder)
	// has query string is very big and can't be handled directly by C++ compiler due to its limitation on string length.
	if (db_queryname == "create_db_schema") {
		query = readFile(dbschema_filename);
	}
		else query = db_query_definitions[index].query;
	query.Replace("%DBNAME%", dbname);
	query.Replace("%USERNAME%", db_username);
	return query;
}

//////////////////////////////////////////////////



// OpenTracker Stats Management //////////////////

OTDLL_API_QUERYDEFS int OT_DLL_GetNumberOfStats() {
	return k_number_of_opentracker_stats;
}

// We create queries on the fly, 
// so that they are usable for both ring-games and tournaments 
const char* const k_holdem_id  = "1";
const char* const k_omaha_id  = "2";
const char* const k_tournament_infix = "tourney";
const char* const k_cashgame_infix = "cash";

// Values of all stats for all players
double stats[k_number_of_opentracker_stats][kMaxNumberOfPlayers];

OTDLL_API_QUERYDEFS CString OT_DLL_GetStatQuery(
	    int stats_index, 
      bool isomaha, 
      bool istournament,
	    int site_id, 
      CString player_name,
      double big_blind) {
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	CString query = stat_query_definitions[stats_index].query;
	CString site_id_as_string;
	site_id_as_string.Format("%i", site_id);
	query.Replace("%SITEID%", site_id_as_string);
	query.Replace("%SCREENNAME%", player_name);
	query.Replace("%GAMETYPE%", (isomaha ? k_omaha_id : k_holdem_id) );
	query.Replace("%TYPE%", (istournament ? k_tournament_infix : k_cashgame_infix));
	return query;
}

OTDLL_API_QUERYDEFS CString OT_DLL_GetDescription(int stats_index) { 
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	return stat_query_definitions[stats_index].description_for_editor; 
}

OTDLL_API_QUERYDEFS CString OT_DLL_GetBasicSymbolNameWithoutPTPrefix(int stats_index) {
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	return stat_query_definitions[stats_index].name;
}	

OTDLL_API_QUERYDEFS bool OT_DLL_IsBasicStat(int stats_index) { 
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	return stat_query_definitions[stats_index].stat_group == ot_group_basic; 
}

OTDLL_API_QUERYDEFS bool OT_DLL_IsPositionalPreflopStat(int stats_index) { 
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	return stat_query_definitions[stats_index].stat_group == ot_group_positional;
}

OTDLL_API_QUERYDEFS bool OT_DLL_IsAdvancedStat(int stats_index) { 
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	return stat_query_definitions[stats_index].stat_group == ot_group_advanced; 
}

// Not exported
CString PureSymbolName(CString symbol_name) {
	// Cut off "ot_" prefix for other chairs
	if (symbol_name.Left(3) == "ot_") {
		symbol_name = symbol_name.Right(symbol_name.GetLength() - 3);
		// Cut off chair number at the right end
		char last_character = symbol_name[symbol_name.GetLength() - 1];
		if (isdigit(last_character)) {
			symbol_name = symbol_name.Left(symbol_name.GetLength() - 1);
		}	
  }
  return symbol_name;
}

// Not exported
int GetStatQueryIndex(CString symbol_name) {
	assert(symbol_name != "");
	symbol_name = PureSymbolName(symbol_name);
	// This function can (and should) probably be optimized
	// by use of CMaps (binary trees).
	for (int i=0; i<k_number_of_opentracker_stats; ++i) {
		if (symbol_name == stat_query_definitions[i].name) {
			return i;
		}
	}
	return kUndefined;
}

OTDLL_API_QUERYDEFS double	OT_DLL_GetStat(CString symbol_name, int chair) {
	assert(symbol_name != "");
	symbol_name = PureSymbolName(symbol_name);
	AssertRange(chair, kFirstChair, kLastChair);
	int stats_index = GetStatQueryIndex(symbol_name);
	if (stats_index == kUndefined) {
		return kUndefined;
	}
	return stats[stats_index][chair];
}

OTDLL_API_QUERYDEFS void OT_DLL_SetStat(int stats_index, int chair, double value) {
	AssertRange(stats_index, 0, (k_number_of_opentracker_stats - 1));
	AssertRange(chair, kFirstChair, kLastChair);
	stats[stats_index][chair] = value;
}

OTDLL_API_QUERYDEFS bool OT_DLL_IsValidSymbol(CString symbol_name) {
	return (GetStatQueryIndex(symbol_name) >= 0);
}

OTDLL_API_QUERYDEFS void OT_DLL_ClearPlayerStats(int chair) {
	AssertRange(chair, kFirstChair, kLastChair);
	for (int i=0; i<k_number_of_opentracker_stats; ++i) {
		OT_DLL_SetStat(i, chair, kUndefined);
	}
}

OTDLL_API_QUERYDEFS void OT_DLL_ClearAllPlayerStats() {
	for (int i=0; i<kMaxNumberOfPlayers; ++i) {
		OT_DLL_ClearPlayerStats(i);
	}
}

/////////////////////////////////////////////