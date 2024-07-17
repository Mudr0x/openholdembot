#pragma once

#include "util.h"
#include "OpenHoldemFunctions.h"


#include <stdio.h>

/*
OpenHoldem Variables

OH_VAR(x) - double variable
OH_VAR_INT(x) - OH variable casted to an int
OH_VAR_UNSIGNED_INT(x) - OH variable casted to an unsigned int
OH_VAR_BOOL(x) - OH variable casted to an bool
OH_SEAT_VAR(x) - OH double variable that is applicable to all seats (becomes and array of values)

For all OH variables use: dirty_x();
*/

#define OH_VAR(x) \
	protected:\
	double priv##x;\
	bool b_dirty_##x;\
	public:\
	void dirty_##x() { b_dirty_##x = true; }\
	double get_##x() \
{ \
	if (b_dirty_##x) { \
	priv##x = GetSymbol(#x);\
	b_dirty_##x = false;\
	} \
	return priv##x; \
};

#define OH_VAR_INT(x) \
	protected:\
	int priv##x;\
	bool b_dirty_##x;\
	public:\
	void dirty_##x() { b_dirty_##x = true; }\
	int get_##x() \
{ \
	if (b_dirty_##x) { \
	priv##x = static_cast<int>(GetSymbol(#x));\
	b_dirty_##x = false;\
	} \
	return priv##x; \
};

#define OH_VAR_UNSIGNED_INT(x) \
	protected:\
	unsigned int priv##x;\
	bool b_dirty_##x;\
	public:\
	void dirty_##x() { b_dirty_##x = true; }\
	unsigned int get_##x() \
{ \
	if (b_dirty_##x) { \
	priv##x = static_cast<unsigned int>(GetSymbol(#x));\
	b_dirty_##x = false;\
	} \
	return priv##x; \
};

#define OH_VAR_BOOL(x) \
	protected:\
	bool priv##x;\
	bool b_dirty_##x;\
	public:\
	void dirty_##x() { b_dirty_##x = true; }\
	bool get_##x() \
{ \
	if (b_dirty_##x) { \
	priv##x = IsEqual(GetSymbol(#x), 1.0 ? true : false);\
	b_dirty_##x = false;\
	} \
	return priv##x; \
};

#define OH_SEAT_VAR(x) \
	protected:\
	double priv##x[10];\
	bool b_dirty_##x[10];\
	public:\
	void dirty_##x(int iSeat) { b_dirty_##x[iSeat] = true; }\
	double get_##x(int iSeat) \
{ \
	if (b_dirty_##x[iSeat]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iSeat);\
	priv##x[iSeat] = GetSymbol(query);\
	b_dirty_##x[iSeat] = false;\
	} \
	return priv##x[iSeat]; \
};

#define OH_SEAT_VAR_INT(x) \
	protected:\
	int priv##x[10];\
	bool b_dirty_##x[10];\
	public:\
	void dirty_##x(int iSeat) { b_dirty_##x[iSeat] = true; }\
	int get_##x(int iSeat) \
{ \
	if (b_dirty_##x[iSeat]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iSeat);\
	priv##x[iSeat] = static_cast<int>(GetSymbol(query));\
	b_dirty_##x[iSeat] = false;\
	} \
	return priv##x[iSeat]; \
};

#define OH_SEAT_VAR_UNSIGNED_INT(x) \
	protected:\
	unsigned int priv##x[10];\
	bool b_dirty_##x[10];\
	public:\
	void dirty_##x(int iSeat) { b_dirty_##x[iSeat] = true; }\
	unsigned int get_##x(int iSeat) \
{ \
	if (b_dirty_##x[iSeat]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iSeat);\
	priv##x[iSeat] = static_cast<unsigned int>(GetSymbol(query));\
	b_dirty_##x[iSeat] = false;\
	} \
	return priv##x[iSeat]; \
};

#define OH_SEAT_VAR_BOOL(x) \
	protected:\
	bool priv##x[10];\
	bool b_dirty_##x[10];\
	public:\
	void dirty_##x(int iSeat) { b_dirty_##x[iSeat] = true; }\
	bool get_##x(int iSeat) \
{ \
	if (b_dirty_##x[iSeat]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iSeat);\
	priv##x[iSeat] = IsEqual(GetSymbol(#x), 1.0 ? true : false);\
	b_dirty_##x[iSeat] = false;\
	} \
	return priv##x[iSeat]; \
};

#define OH_ROUND_VAR(x) \
	protected:\
	double priv##x[5];\
	bool b_dirty_##x[5];\
	public:\
	void dirty_##x(int iRound) { b_dirty_##x[iRound] = true; }\
	double get_##x(int iRound) \
{ \
	if (b_dirty_##x[iRound]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iRound);\
	priv##x[iRound] = GetSymbol(query);\
	b_dirty_##x[iRound] = false;\
	} \
	return priv##x[iRound]; \
};

#define OH_ROUND_VAR_INT(x) \
	protected:\
	int priv##x[5];\
	bool b_dirty_##x[5];\
	public:\
	void dirty_##x(int iRound) { b_dirty_##x[iRound] = true; }\
	int get_##x(int iRound) \
{ \
	if (b_dirty_##x[iRound]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iRound);\
	priv##x[iRound] = static_cast<int>(GetSymbol(query));\
	b_dirty_##x[iRound] = false;\
	} \
	return priv##x[iRound]; \
};

#define OH_ROUND_VAR_UNSIGNED_INT(x) \
	protected:\
	unsigned int priv##x[5];\
	bool b_dirty_##x[5];\
	public:\
	void dirty_##x(int iRound) { b_dirty_##x[iRound] = true; }\
	unsigned int get_##x(int iRound) \
{ \
	if (b_dirty_##x[iRound]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iRound);\
	priv##x[iRound] = static_cast<unsigned int>(GetSymbol(query));\
	b_dirty_##x[iRound] = false;\
	} \
	return priv##x[iRound]; \
};

#define OH_ROUND_VAR_BOOL(x) \
	protected:\
	bool priv##x[5];\
	bool b_dirty_##x[5];\
	public:\
	void dirty_##x(int iRound) { b_dirty_##x[iRound] = true; }\
	bool get_##x(int iRound) \
{ \
	if (b_dirty_##x[iRound]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iRound);\
	priv##x[iRound] = IsEqual(GetSymbol(#x), 1.0 ? true : false);\
	b_dirty_##x[iRound] = false;\
	} \
	return priv##x[iRound]; \
};

#define OH_SUIT_VAR_UNSIGNED_INT(x) \
	protected:\
	unsigned int priv##x[4];\
	bool b_dirty_##x[4];\
	public:\
	void dirty_##x(int iSuit) { b_dirty_##x[iSuit] = true; }\
	unsigned int get_##x(int iSuit) \
{ \
	if (b_dirty_##x[iSuit]) { \
	char query[255];\
	sprintf(query, "%s%d", #x, iSuit);\
	priv##x[iSuit] = static_cast<unsigned int>(GetSymbol(query));\
	b_dirty_##x[iSuit] = false;\
	} \
	return priv##x[iSuit]; \
};
