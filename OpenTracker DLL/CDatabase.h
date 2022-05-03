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
#define OTDLL_API_DATABASE __declspec(dllexport)
#else
#define OTDLL_API_DATABASE __declspec(dllimport)
#endif


// http://www.postgresql.org/docs/8.1/static/libpq.html
#include "libpq-fe.h"



class OTDLL_API_DATABASE	CDatabase
{
public:
	CDatabase();
	~CDatabase();

public:
	CString	CreatePQconnectionString(const CString ip_address,
		const CString port, const CString username,
		const CString password);
	CString	CreateDBconnectionString(const CString ip_address,
		const CString port, const CString username,
		const CString password, const CString DB_name);
	void SetDBconnectEntries(CString ip_addr, CString port, CString user, CString pass, CString dbname) {
		_ip_addr = ip_addr; _port = port; _user = user; _pass = pass; _dbname = dbname;
	};
	void SetPGconn(PGconn*	pgconn) { _pgconn = pgconn;	}
	bool PQconnect(bool onDB = false);
	bool IsDBexists(CString dbname);
	bool QueryPostGreSQL(CString dbname, CString query);
	void CreateOpenTrackerDB(CString dbname, CString username);

private:
	void SetResult(double result) { _result = result; };
	double GetResult() { return _result; };
	CString GetDBname() { return _dbname; };
	CString GetUsername() { return _user; };

	CString _ip_addr, _port, _user, _pass, _dbname;
	double _result;

	PGconn*	_pgconn;
};

extern CDatabase *p_otdb_thread;


