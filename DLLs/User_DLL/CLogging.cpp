#include "CLogging.h"

#include <conio.h>
#include <ctime>
#include <iostream>

#include "CSymbols.h"

CLogging::CLogging() : 
	_b_direct_to_console(true), 
	_b_direct_to_file(true), 
	_error_log(NULL), 
	_p_console(0)
{
	for(int i=0; i<eCatLastItem; i++)
		_bOutputCategory[i] = true;

	//m_bOutputCategory[eCatGeneral] = false;

	Init();
}

void CLogging::Init()
{
	if(_b_direct_to_console && !_p_console) 
	{
		AllocConsole();
		_p_console = GetStdHandle(STD_OUTPUT_HANDLE);
		//UINT oldcodepage = GetConsoleOutputCP();
		//SetConsoleOutputCP(437);
	}

	if(_b_direct_to_file && !_error_log) 
	{
		char logname[MAX_PATH], _startup_path[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH - 1, _startup_path);
		sprintf_s(logname, "%s\\minion_%u.log", 
			_startup_path, 
			static_cast<unsigned int>(time(NULL)));

		fopen_s(&_error_log, logname, "a+");
	}
}

void CLogging::Close()
{
	if(_p_console) 
	{
		_p_console = 0;
		FreeConsole();
	}

	if(_error_log) 
	{
		fclose(_error_log);
		_error_log = NULL;
	}
}

void CLogging::WriteLog(eSeverity iSeverity, eCategory iCategory, const char * _Format, ...)
{
	if(iSeverity < eSeverityDebug && !_bOutputCategory[iCategory])
		return;

	bool log_console = _b_direct_to_console;
	bool log_file = (_b_direct_to_file && _error_log);
	if(log_console || log_file)
	{
		time_t t = time(&t);
		struct tm ts;
		localtime_s(&ts, &t);
		strftime(_short_timebuf, sizeof(_short_timebuf), "%X", &ts);

		if(log_console)
		{
			SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			_cprintf("%s [h:%d | br:%d] ", 
				_short_timebuf, 
				g_symbols->get_handsplayed(), 
				g_symbols->get_betround());
		}

		if(log_file)
		{
			fprintf(_error_log, "%s [h:%d | br:%d] ", 
				_short_timebuf, 
				g_symbols->get_handsplayed(), 
				g_symbols->get_betround());
		}
	}

	va_list argList;
	va_start(argList, _Format);
	DoWriteLog(iSeverity, iCategory, _Format, argList);
	va_end(argList);
}

void CLogging::WriteLogNoHeading(eSeverity iSeverity, eCategory iCategory, const char * _Format, ...)
{
	if(iSeverity < eSeverityDebug && !_bOutputCategory[iCategory])	
		return;

	va_list argList;
	va_start(argList, _Format);
	DoWriteLog(iSeverity, iCategory, _Format, argList);
	va_end(argList);
}

void CLogging::DoWriteLog(eSeverity iSeverity, eCategory iCategory, const char * _Format, va_list argList)
{
	if(_b_direct_to_file && _error_log) 
	{
		vfprintf(_error_log, _Format, argList); 
		fflush(_error_log);
	}

	if(_b_direct_to_console) 
	{
		// gray
		SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

		if(iCategory == eCatHandHistory) 
		{
			// cyan
			SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		else if(iCategory == eCatOpponentModeling) 
		{
			// yellow
			SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		else if(iCategory == eCatGeneral) 
		{
			// yellow on blue
			SetConsoleTextAttribute(_p_console, 0 | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		else if (iCategory == eCatDecision)
		{
			// green
			SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}

		else if (iCategory == eCatInfo)
		{
			// green
			SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}

		if(iSeverity == eSeverityDebug) 
		{
			// red on light yellow
			SetConsoleTextAttribute(_p_console, 0 | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED);
			//Beep(750, 200);
		}
		else if(iSeverity >= eSeverityError)
		{
			// yellow on red
			SetConsoleTextAttribute(_p_console, 0 | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			//Beep(750, 200);
		}

		// Color Fix :P
		const char *pch = strchr(_Format,'\n');
		if(pch!=NULL)
		{
			size_t len = pch - _Format;
			memcpy(_sz_buffer, _Format, len);
			if (len > 0)
			{
				_sz_buffer[len] = '\0';
				_vcprintf(_sz_buffer, argList);
				SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
				_cprintf("\n");
			}
		}
		else
		{
			_vcprintf(_Format, argList);
			SetConsoleTextAttribute(_p_console, 0 | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
		}
	}
}
