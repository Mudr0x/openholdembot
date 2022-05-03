#include "stdafx.h"
#include "COpenTrackerLookup.h"


#include "..\CTablemap\CTablemap.h"

COpenTrackerLookup ot_lookup;

COpenTrackerLookup::COpenTrackerLookup() {
	_ot_siteid.clear();
	// Documentation about PT3 sited_IDs:
	// http://www.pokertracker.com/forums/viewtopic.php?f=18&t=20169&p=95629
	// All sitenames and networknames have to be in LOWER-CASES!
	_ot_siteid.insert(std::pair<CString, int> ("stars", 100));
	_ot_siteid.insert(std::pair<CString, int> ("party", 200));
	_ot_siteid.insert(std::pair<CString, int> ("fulltilt", 300));
	_ot_siteid.insert(std::pair<CString, int> ("ipoker", 400));
	_ot_siteid.insert(std::pair<CString, int> ("everest", 500));
	_ot_siteid.insert(std::pair<CString, int> ("ongame", 600));
	_ot_siteid.insert(std::pair<CString, int> ("boss", 700));
	_ot_siteid.insert(std::pair<CString, int> ("cereus", 800));
	_ot_siteid.insert(std::pair<CString, int> ("pacific", 900));
	_ot_siteid.insert(std::pair<CString, int> ("b2b", 1000));
	_ot_siteid.insert(std::pair<CString, int> ("microgaming", 1100));
	_ot_siteid.insert(std::pair<CString, int> ("cake", 1200));
	_ot_siteid.insert(std::pair<CString, int> ("bodog", 1300));
	_ot_siteid.insert(std::pair<CString, int> ("betfair", 1400));
	_ot_siteid.insert(std::pair<CString, int> ("cryptologic", 1500));
	_ot_siteid.insert(std::pair<CString, int> ("ultimate", 1600));
	_ot_siteid.insert(std::pair<CString, int> ("absolute", 1700));
	_ot_siteid.insert(std::pair<CString, int> ("wpex", 1800));
	_ot_siteid.insert(std::pair<CString, int> ("tribeca", 1900));
	// 2000 not (yet) supported, whatever it is
	_ot_siteid.insert(std::pair<CString, int> ("merge", 2100));
	_ot_siteid.insert(std::pair<CString, int> ("winamax", 2200));
	_ot_siteid.insert(std::pair<CString, int> ("everleaf", 2300));
	_ot_siteid.insert(std::pair<CString, int> ("yatahay", 2400));
	_ot_siteid.insert(std::pair<CString, int> ("enet", 2500));
	_ot_siteid.insert(std::pair<CString, int> ("barriere", 2600));
	// 2700 not (yet) supported, whatever it is
	_ot_siteid.insert(std::pair<CString, int> ("peoples", 2800));
}

COpenTrackerLookup::~COpenTrackerLookup() {
  _ot_siteid.clear();
}

const int COpenTrackerLookup::GetSiteId()
{
	// Is s$sitename or s$network one of the supported OT sites? 
	// Return the proper site_id for db queries.
	//
	// No longer requiring an exact match for manualmode,
  // but treating it like a normal casino.
  // http://www.maxinmontreal.com/forums/viewtopic.php?f=114&t=12158&p=108712#p108712

	std::map<CString, int>::const_iterator lookup, end;
	lookup = _ot_siteid.begin();
	end = _ot_siteid.end();

	CString sitename = p_tablemap->sitename();
	CString network = p_tablemap->network();

	while (lookup!=end)
	{
		CString supported_sitename = lookup->first;
		if (sitename.MakeLower().Find(supported_sitename.MakeLower()) >= 0
			|| network.CompareNoCase(supported_sitename) == 0)
		{
			write_log(Preferences()->debug_opentracker(), "[OpenTrackerLookup] Site or network is: %s\n",
				supported_sitename);
			write_log(Preferences()->debug_opentracker(), "[OpenTrackerLookup] SiteID is %i\n",
				lookup->second);
			return lookup->second;
		}
		lookup++;
	}
	write_log(Preferences()->debug_opentracker(), 
		"[OpenTrackerLookup] ERROR: unsupported sitename and unsupported network.\n");
	write_log(Preferences()->debug_opentracker(), 
		"[OpenTrackerLookup] Probably wrong data in tablemap.\n");
	return -1;
}