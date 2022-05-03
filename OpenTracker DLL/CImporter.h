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
#define OTDLL_API_IMPORTER __declspec(dllexport)
#else
#define OTDLL_API_IMPORTER __declspec(dllimport)
#endif


#include "libpq-fe.h"



class OTDLL_API_IMPORTER	CImporter
{
public:
	CImporter();
	~CImporter();

public:
	void StartThread();
	void StopThread();
	bool IsConnected();
	void Connect();
	void Reconnect(void);
	void Disconnect();
	void GetHandsManual(CString poknet_name, CString hhpath, CString tspath = "");

private:
	static UINT	OTImporterThreadFunction(LPVOID pParam);
	bool AllConnectionDataSpecified();
	bool QueryPostGreSQL(CString dbname, CString query);
	bool IsFileStored(CString filename, CString poknet_name);
	void StoreFile(CString filename, CString poknet_name);
	bool IsDirExists(CString path);

	CString			_conn_str;
	bool			_connected;

	HANDLE			_m_stop_thread;
	HANDLE			_m_wait_thread;

	CWinThread	*_otimp_thread;
	PGconn*	_pgconn;

	CString _filename;		
};

