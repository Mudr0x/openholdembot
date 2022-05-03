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


#include "stdafx.h"
#include <comdef.h>
using namespace std;

#include "CDatabase.h"
#include "opentracker_query_definitions.h"
#include "..\DLLs\WindowFunctions_DLL\window_functions.h"


CDatabase::CDatabase()
{
}

CDatabase::~CDatabase()
{
}

CString	CDatabase::CreatePQconnectionString(const CString ip_address,
	const CString port, const CString username,
	const CString password)
{
	CString result;
	result.Format("host=%s port=%s user=%s password=%s",
		ip_address, port, username, password);
	write_log(Preferences()->debug_opentracker(), "[OpenTracker] PQ Connection-string: %s\n", result);
	return result;

}

CString	CDatabase::CreateDBconnectionString(const CString ip_address,
	const CString port, const CString username,
	const CString password, const CString dbname)
{
	CString result;
	result.Format("host=%s port=%s user=%s password=%s dbname='%s'",
		ip_address, port, username, password, dbname);
	write_log(Preferences()->debug_opentracker(), "[OpenTracker] DB Connection-string: %s\n", result);
	return result;
}

bool CDatabase::PQconnect(bool onDB) {
	CString			conn_str = "", e = "";

	if (onDB)
		conn_str = CreateDBconnectionString(_ip_addr,
			_port, _user, _pass, _dbname);
	else
		conn_str = CreatePQconnectionString(_ip_addr,
			_port, _user, _pass);

	// Set busy cursor
	CWaitCursor wait;

	// Test the connection parameters
	_pgconn = PQconnectdb(conn_str.GetString());

	if (PQstatus(_pgconn) == CONNECTION_OK) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Connect DB: PostgreSQL DB connected successfully <%s/%s/%s>\n", _ip_addr, _port, _dbname);
		if (PQisthreadsafe()) {
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Connect DB: PostgreSQL library is thread safe.\n\n");
			//MessageBox_Interactive("PostgreSQL DB connected successfully", "Success", MB_OK);
		}
		else {
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Connect DB: PostgreSQL library is *NOT* thread safe!  This is a problem!\n\n");
			MessageBox_Interactive("PostgreSQL DB connected successfully, but\nPostgreSQL library is *NOT* thread safe!\nThis is a problem!",
				"Success (partial)", MB_OK);
		}
		return true;
	}
	else {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Connect DB: ERROR connecting PostgreSQL DB: %s\n\n", PQerrorMessage(_pgconn));
		e = "ERROR connecting PostgreSQL DB:\n";
		e += PQerrorMessage(_pgconn);
		e += "\nConn string:";
		e += conn_str;

		MessageBox_Interactive(e.GetString(), "ERROR", MB_OK);
		return false;
	}
}

bool CDatabase::IsDBexists(CString dbname) {
	PGresult* result = NULL;

	CString query;
	query.Format("select exists(SELECT datname FROM pg_catalog.pg_database WHERE datname = '%s')",
		dbname);
	result = PQexec(_pgconn, query);

	CString reply = PQgetvalue(result, 0, 0);
	if (reply == 't')
		return true;
	// We got nothing, return false
	else
		return false;
}

bool CDatabase::QueryPostGreSQL(CString dbname, CString query) {
	PGresult* res = NULL;
	double	result = kUndefined;
	CString e = "";
	clock_t	updStart, updEnd;
	int		duration;


	// Do the query against the OT database
	updStart = clock();
	try
	{
		// Querying against PostgreSQL
		write_log(Preferences()->debug_opentracker(),
			"[OpenTracker] Query DB: Querying against %s DB\n\n", dbname);

		// Set busy cursor
		CWaitCursor wait;

		// Execute the query against OT DB
		res = PQexec(_pgconn, query);
	}
	catch (_com_error &e)
	{
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: ERROR\n");
		write_log(Preferences()->debug_opentracker(), _T("\tCode = %08lx\n"), e.Error());
		write_log(Preferences()->debug_opentracker(), _T("\tCode meaning = %s\n"), e.ErrorMessage());
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		write_log(Preferences()->debug_opentracker(), _T("\tSource = %s\n"), (LPCTSTR)bstrSource);
		write_log(Preferences()->debug_opentracker(), _T("\tDescription = %s\n"), (LPCTSTR)bstrDescription);
		write_log(Preferences()->debug_opentracker(), _T("\tQuery = [%s]\n\n"), query);
	}

	updEnd = clock();
	duration = (int)((double)(updEnd - updStart) / 1000);
	if (duration >= 3)
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: Query time in seconds: [%d]\n\n", duration);

	// Check query return code
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		switch (PQresultStatus(res))
		{
		case PGRES_COMMAND_OK:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: PGRES_COMMAND_OK: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		case PGRES_EMPTY_QUERY:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: PGRES_EMPTY_QUERY: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		case PGRES_BAD_RESPONSE:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Create DB: PGRES_BAD_RESPONSE: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		case PGRES_COPY_OUT:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: PGRES_COPY_OUT: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		case PGRES_COPY_IN:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: PGRES_COPY_IN: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		case PGRES_NONFATAL_ERROR:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: PGRES_NONFATAL_ERROR: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		case PGRES_FATAL_ERROR:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: PGRES_FATAL_ERROR: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		default:
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Query DB: GENERIC ERROR: %s [%s]\n\n", PQerrorMessage(_pgconn), query);
			break;
		}
		CString PQerr = PQerrorMessage(_pgconn);
		if (PQerr != "") {
			e = "ERROR querying OpenTracker DB:\n";
			e += PQerr;

			MessageBox_Interactive(e.GetString(), "ERROR", MB_OK);
			PQfinish(_pgconn);
			return false;
		}
		else {
			if (PQgetisnull(res, 0, 0) != 1)
			{
				result = atof(PQgetvalue(res, 0, 0));
				write_log(Preferences()->debug_opentracker(),
					"[OpenTracker] Query DB: Query success against %s DB: %f\n\n", dbname, result);
				SetResult(result);
			}

			PQclear(res);
			return true;
		}
	}
	else
	{	
		if (PQgetisnull(res, 0, 0) != 1)
		{
			result = atof(PQgetvalue(res, 0, 0));
			write_log(Preferences()->debug_opentracker(),
				"[OpenTracker] Query DB: Query success against %s DB: %f\n\n", dbname, result);
			SetResult(result);
		}

		PQclear(res);
		return true;
	}
}

void CDatabase::CreateOpenTrackerDB(CString dbname, CString username) {
	CString query = OT_DLL_GetDBQuery("drop_db", dbname, username);
	if (QueryPostGreSQL(dbname, query)) {
		query = OT_DLL_GetDBQuery("create_db", dbname, username);
		if (QueryPostGreSQL(dbname, query)) {
			query = OT_DLL_GetDBQuery("alter_db", dbname, username);
			if (QueryPostGreSQL(dbname, query)) {
				if (PQconnect(true)) {
					query = OT_DLL_GetDBQuery("create_db_schema", dbname, username);
					if (QueryPostGreSQL(dbname, query)) {
						write_log(Preferences()->debug_opentracker(),
							"[OpenTracker] Create DB: Query success for %s DB creation.\nOpenTracker DB created successfully.\n\n", dbname);
						MessageBox_Interactive("OpenTracker DB created successfully", "Success", MB_OK);
					}
				}
			}
		}
	}
	PQfinish(_pgconn);
}