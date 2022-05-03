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

#include <string>
#include <iostream>
#include <stdio.h>
#include "dirent.h"
#include <sys/types.h>
#include <chrono>
using namespace std;
using namespace chrono;

#include "CImporter.h"
#include "CDatabase.h"
#include "opentracker_query_definitions.h"
#include "..\DLLs\WindowFunctions_DLL\window_functions.h"

CDatabase OT_DB;


CImporter::CImporter()
{
	// Initialize variables
	_otimp_thread = NULL;

	_conn_str = OT_DB.CreateDBconnectionString(Preferences()->ot_ip_addr(),
		Preferences()->ot_port(), Preferences()->ot_user(), Preferences()->ot_pass(), Preferences()->ot_dbname());

	_connected = false;
	_m_stop_thread = NULL;
	_m_wait_thread = NULL;
	_pgconn = NULL;
}

CImporter::~CImporter()
{
	StopThread();
}


void CImporter::StartThread()
{
	if (!AllConnectionDataSpecified())
	{
		return;
	}
	if (_otimp_thread == NULL)
	{
		// Create events
		_m_stop_thread = CreateEvent(0, TRUE, FALSE, 0);
		_m_wait_thread = CreateEvent(0, TRUE, FALSE, 0);

		_otimp_thread = AfxBeginThread(OTImporterThreadFunction, this);

		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Started OpenTracker-thread.\n");
	}
	else
	{
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] OpenTracker-thread already running.\n");
	}
}

void CImporter::StopThread()
{
	if (_otimp_thread)
	{
		// Trigger thread to stop
		::SetEvent(_m_stop_thread);

		// Wait until thread finished
		::WaitForSingleObject(_m_wait_thread, k_max_time_to_wait_for_thread_to_shutdown);

		_otimp_thread = NULL;

		Disconnect();

		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Stopped Poker Tracker thread.\n");
	}

	// Close handles
	if (_m_stop_thread)
	{
		::CloseHandle(_m_stop_thread);
		_m_stop_thread = NULL;
	}
	if (_m_wait_thread)
	{
		::CloseHandle(_m_wait_thread);
		_m_wait_thread = NULL;
	}
}


UINT CImporter::OTImporterThreadFunction(LPVOID pParam) {
	CImporter *pParent = static_cast<CImporter*>(pParam);

	while (::WaitForSingleObject(pParent->_m_stop_thread, 0) != WAIT_OBJECT_0) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] OTthread had started\n");
		if (!pParent->_connected) {
			pParent->Connect();
		}
		else if (PQstatus(pParent->_pgconn) != CONNECTION_OK) {
			pParent->Reconnect();
		}
	}
	// Set event
	write_log(Preferences()->debug_opentracker(), "[OpenTracker] OpentrackerThreadFunction: outside while loop...\n");
	::SetEvent(pParent->_m_wait_thread);
	return 0;
}

bool CImporter::AllConnectionDataSpecified()
{
	return(Preferences()->ot_ip_addr() != ""
		&& Preferences()->ot_port() != ""
		&& Preferences()->ot_user() != ""
		&& Preferences()->ot_pass() != ""
		&& Preferences()->ot_dbname() != "");
}

void CImporter::Connect(void) {
	write_log(Preferences()->debug_opentracker(), "[OpenTracker] Trying to open PostgreSQL DB...\n");
	if (!AllConnectionDataSpecified()) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Can't connect to DB. Vital data missing\n");
		return;
	}
	_conn_str = OT_DB.CreateDBconnectionString(Preferences()->ot_ip_addr(),
		Preferences()->ot_port(), Preferences()->ot_user(), Preferences()->ot_pass(), Preferences()->ot_dbname());
	_pgconn = PQconnectdb(_conn_str.GetString());

	if (PQstatus(_pgconn) == CONNECTION_OK) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] PostgreSQL DB opened successfully <%s/%s/%s>\n",
			Preferences()->ot_ip_addr(),
			Preferences()->ot_port(),
			Preferences()->ot_dbname());

		_connected = true;
	}
	else {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] ERROR opening PostgreSQL DB: %s\n\n", PQerrorMessage(_pgconn));
		PQfinish(_pgconn);
		_connected = false;
		_pgconn = NULL;
	}
}

void CImporter::Reconnect(void) {
	// Reconnecting after a lost network connection
	// http://www.maxinmontreal.com/forums/viewtopic.php?f=214&t=19553
	if (_pgconn) {
		if (PQstatus(_pgconn) != CONNECTION_OK) {
			PQreset(_pgconn);
			if (PQstatus(_pgconn) == CONNECTION_OK) {
				write_log(Preferences()->debug_opentracker(), "[OpenTracker] PostgreSQL DB reconnected after bad connection\n");
				_connected = true;
			}
			else {
				write_log(Preferences()->debug_opentracker(), "[OpenTracker] ERROR reconnecting to PostgreSQL DB: %s\n\n", PQerrorMessage(_pgconn));
				PQfinish(_pgconn);
				_connected = false;
				_pgconn = NULL;
			}
		}
	}
}

void CImporter::Disconnect(void) {
	if (_pgconn) {
		if (PQstatus(_pgconn) == CONNECTION_OK) {
			PQfinish(_pgconn);
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Disconnected");
		}
	}
	_pgconn = NULL;
	_connected = false;
}

bool CImporter::IsConnected() {
	write_log(Preferences()->debug_opentracker(), "[OpenTracker] connected: %s\n",
		Bool2CString(_connected));
	write_log(Preferences()->debug_opentracker(), "[OpenTracker]PXStatus = %d (0 = CONNECTION_OK)\n",
		PQstatus(_pgconn));
	return (_connected && PQstatus(_pgconn) == CONNECTION_OK);
}


bool CImporter::IsFileStored(CString filename, CString poknet_name) {
	PGresult* result = NULL;

	CString query;
	query.Format("select exists(SELECT id FROM files WHERE file = '%s' AND site = '%s')",
		filename, poknet_name);

	result = PQexec(_pgconn, query);

	CString reply = PQgetvalue(result, 0, 0);
	if (reply == 't')
		return true;
	// We got nothing, return false
	else
		return false;
}

void CImporter::StoreFile(CString filename, CString poknet_name) {
	PGresult* result = NULL;

	time_t rawtime;
	struct tm *ptm;
	// Get number of seconds since 00:00 UTC Jan, 1, 1970 and store in rawtime
	time(&rawtime);
	// UTC struct tm
	ptm = gmtime(&rawtime);
	microseconds ms = duration_cast< microseconds >(
		system_clock::now().time_since_epoch()
		);
	long long msdur = static_cast<long long>(ms.count());
	CString micsec;
	micsec.Format("%lld", msdur);
	micsec = micsec.Right(6);

	CString date;
	date.Format("%0002d-%02d-%02d %02d:%02d:%02d.%000002s", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, micsec);

	CString query;
	query.Format("INSERT INTO files(file, site, start_time, last_update, hands, stored, dups, partial, errs, ttime100, finished) \
					VALUES ('%s', '%s', '%s', '%s', 0, 0, 0, 0, 0, 0, false)",
		filename, poknet_name, date, date);
	result = PQexec(_pgconn, query);

	CString reply = PQgetvalue(result, 0, 0);
}

bool CImporter::IsDirExists(CString path) {
	DIR *dir = opendir(path);

	if (dir == NULL) {
		return false;
	}

	return true;
}

void CImporter::GetHandsManual(CString poknet_name, CString hhpath, CString tspath) {
	struct dirent *entry;
	DIR *dir = opendir(hhpath);

	if (!IsDirExists(hhpath)) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Get Hands Manual: Hand History folder isn't set or doesn't exist! Get Hands cancelled.\n\n");
		MessageBox_Interactive("Hand History folder isn't set or doesn't exist!\nYou must set a valid folder you want to get hands on.",
			"Warning", MB_OK);
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		_filename = entry->d_name;
		if (!IsFileStored(_filename, poknet_name) && _filename != "." && _filename != "..") {
			StoreFile(_filename, poknet_name);
		}
	}

	closedir(dir);
}

bool CImporter::QueryPostGreSQL(CString dbname, CString query) {
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
				//SetResult(result);
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
			//SetResult(result);
		}

		PQclear(res);
		return true;
	}
}