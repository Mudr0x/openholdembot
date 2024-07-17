#pragma once

#include "..\..\G5Wrapper\G5Wrapper.h"


class CWrapper
{
public:
	G5Wrapper GetWrapper() { return _wrapper; };
private:
	G5Wrapper _wrapper;

};

extern CWrapper* g_wrapper;

