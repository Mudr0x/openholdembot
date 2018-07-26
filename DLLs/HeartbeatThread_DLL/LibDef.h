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
// Purpose: single import/export macro for all header-files
//
//******************************************************************************

#ifdef HEARTBEATTHREAD_DLL_EXPORTS
#define HEARTBEATTHREAD_DLL_API __declspec(dllexport)
#else
#define HEARTBEATTHREAD_DLL_API __declspec(dllimport)
#endif