
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define SX_DLL
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gdefines.h>

#include <core\\sxcore.cpp>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

