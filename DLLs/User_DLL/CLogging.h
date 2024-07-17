#pragma once

#include <windows.h>
#include <stdio.h>

enum eSeverity
{ 
	eSeverityInfo, 
	eSeverityDebug,
	eSeverityError
};

enum eCategory
{
	eCatInfo,
	eCatGeneral,
	eCatPerformance,
	eCatHandHistory,
	eCatExtractActions,
	eCatBoardTexture, 
	eCatOpponentModeling,
	eCatDecision,
	eCatLastItem 
};

class CLogging
{
public:
	// public methods

	CLogging();

public:
	void WriteLog(eSeverity iSeverity, eCategory iCategory, const char* format, ...);
	void WriteLogNoHeading(eSeverity iSeverity, eCategory iCategory, const char* _Format, ...);
	void Close();

private:
	// Private vars
	bool   _b_direct_to_console, _b_direct_to_file;
	bool   _bOutputCategory[eCatLastItem];
	char   _sz_buffer[2048];
	char   _short_timebuf[26];
	FILE*  _error_log;
	HANDLE _p_console;

private:
		
	// private functions
	void DoWriteLog(eSeverity iSeverity, eCategory iCategory, const char* _Format, va_list argptr);
	void Init();
};

extern CLogging* g_log;