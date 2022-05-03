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

#ifndef INC_COPENTRACKERLOOKUP_H
#define INC_COPENTRACKERLOOKUP_H

#include <map>

class COpenTrackerLookup
{
public:
	// public functions
	COpenTrackerLookup();
	~COpenTrackerLookup();
	const int GetSiteId();

private:
	// private functions and variables - not available via accessors or mutators
	std::map<CString, int>	_ot_siteid;
};

extern COpenTrackerLookup ot_lookup;

#endif INC_COPENTRACKERLOOKUP_H