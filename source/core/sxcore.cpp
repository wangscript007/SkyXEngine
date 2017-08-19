
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define CORE_VERSION 1

#include <core/sxcore.h>

#include <core/loaderconfig.h>

#include <core/file.h>

#include <core/Task.h>
#include <core/TaskManager.h>

#include <core/concmd.h>
#include <core/cvars.h>

#include <core/time.h>

char CoreName[CORE_NAME_MAX_LEN];

#if !defined(DEF_STD_REPORT)
#define DEF_STD_REPORT
report_func reportf = def_report;
#endif
SXTaskManager* TaskManager = 0;

#define SXCORE_PRECOND(retval) if(!TaskManager){reportf(-1, "%s - sxcore is not init", gen_msg_location); return retval;}

//РЕГИСТРЫ
bool GRegistersBool[CORE_REGISTRY_SIZE];
int32_t GRegistersInt[CORE_REGISTRY_SIZE];
float32_t GRegistersFloat[CORE_REGISTRY_SIZE];
float4x4 GRegistersMatrix[CORE_REGISTRY_SIZE];
float3 GRegistersFloat3[CORE_REGISTRY_SIZE];
String GRegistersString[CORE_REGISTRY_SIZE];

#define CORE_REGUSTRY_PRE_COND_ID(id,stdval) \
if (!(id >= 0 && id < CORE_REGISTRY_SIZE))\
{reportf(REPORT_MSG_LEVEL_ERROR, "[CORE] %s - unresolved index '%d' of access for registry", gen_msg_location, id); return stdval; }


TimeManager* Timers = 0;
#define CORE_TIME_PRECOND(retval) if(!Timers){reportf(-1, "%s - sxcore is not init", gen_msg_location); return retval;}

//функции обертки
long Core_0GetVersion()
{
	return CORE_VERSION;
}

void Core_Dbg_Set(report_func rf)
{
	reportf = rf;
}

bool Core_0FileExists(const char* fname)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind = ::FindFirstFile(fname, &wfd);
		if (INVALID_HANDLE_VALUE != hFind)
		{
			::FindClose(hFind);
			return true;
		}
	return false;
}

//---------------------------------

bool Core_0ClipBoardCopy(const char *str)
{
    HGLOBAL hglb;
    char *s;
    int len = strlen(str) + 1;
 
		if(!(hglb = GlobalAlloc(GHND, len)))
			return false;

		if(!(s = (char *)GlobalLock(hglb)))
			return false;

	strcpy(s, str);
	GlobalUnlock(hglb);

		if(!OpenClipboard(NULL) || !EmptyClipboard()) 
		{
			GlobalFree(hglb);
			return false;
		}
	SetClipboardData(CF_TEXT, hglb);
	CloseClipboard();
	return true;
}

bool Core_0IsProcessRun(const char* process)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe);

	while (1) {
		if (stricmp(pe.szExeFile, process) == 0) return true;
		if (!Process32Next(hSnapshot, &pe)) return false;
	}
}

void Core_0Create(const char* name, bool is_unic)
{
		if(name && strlen(name) > 1)
		{
				if(is_unic)
				{
					HANDLE hMutex = CreateMutex(NULL, FALSE, name);
						if(GetLastError() == ERROR_ALREADY_EXISTS)
						{
							CloseHandle(hMutex);
							reportf(-1, "%s - none unic name, sgcore", gen_msg_location);
							return;
						}
				}
			strcpy(CoreName, name);
			ConsoleConnect();
			ConsoleRegisterCmds();
			TaskManager = new SXTaskManager();
			Timers = new TimeManager();
		}
		else
			reportf(-1, "%s - not init argument [name], sgcore", gen_msg_location);
}

void Core_AKill()
{
	SXCORE_PRECOND(_VOID);

	mem_delete(TaskManager);
	ConsoleDisconnect();
}

void Core_AGetName(char* name)
{
	SXCORE_PRECOND(_VOID);

	if(name)
		strcpy(name, CoreName);
	else
		reportf(-1, "%s - invalid argument", gen_msg_location);
}

////

ISXFile* Core_CrFile()
{
	return new SXFile();
}

ISXFile* Core_OpFile(const char* path, int type)
{
	SXFile* tmpsxfile = new SXFile();
	tmpsxfile->Open(path, type);
	return tmpsxfile;
}


ISXLConfig*  Core_CrLConfig()
{
	return new SXLoaderConfig();
}

ISXLConfig*  Core_OpLConfig(const char* path)
{
	SXLoaderConfig* tmplconfig = new SXLoaderConfig();
	tmplconfig->Open(path);
	return tmplconfig;
}

////

void Core_MTaskAdd(THREAD_UPDATE_FUNCTION func, DWORD flag)
{
	SXCORE_PRECOND(_VOID);
	TaskManager->add(func, flag);
}

void Core_MTaskStart()
{
	SXCORE_PRECOND(_VOID);
	TaskManager->start();
}

void Core_MTaskStop()
{
	SXCORE_PRECOND(_VOID);
	TaskManager->stop();
}

//////////////

void Core_RBoolSet(int id, bool val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);
	GRegistersBool[id] = val;
}

bool Core_RBoolGet(int id)
{
	CORE_REGUSTRY_PRE_COND_ID(id, 0);
	return GRegistersBool[id];
}

void Core_RIntSet(int id, int32_t val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);
	GRegistersInt[id] = val;
}

int32_t Core_RIntGet(int id)
{
	CORE_REGUSTRY_PRE_COND_ID(id,0);
	return GRegistersInt[id];
}

void Core_RFloatSet(int id, float32_t val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);
	GRegistersFloat[id] = val;
}

float32_t Core_RFloatGet(int id)
{
	CORE_REGUSTRY_PRE_COND_ID(id,0);
	return GRegistersFloat[id];
}

void Core_RMatrixSet(int id, float4x4* val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);
	if (val)
		GRegistersMatrix[id] = *val;
	else
		GRegistersMatrix[id] = SMMatrixIdentity();
}

void Core_RMatrixGet(int id, float4x4* val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);

	if (val)
		memcpy(val, &GRegistersMatrix[id], sizeof(float4x4));
}


void Core_RFloat3Set(int id, float3* val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);
	if (val)
		GRegistersFloat3[id] = *val;
}

void Core_RFloat3Get(int id, float3* val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);

	if (val)
		memcpy(val, &GRegistersFloat3[id], sizeof(float3));
}

void Core_RStringSet(int id, const char *val)
{
	CORE_REGUSTRY_PRE_COND_ID(id, _VOID);
	if (val)
		GRegistersString[id] = val;
}

const char* Core_RStringGet(int id)
{
	CORE_REGUSTRY_PRE_COND_ID(id, 0);
	return GRegistersString[id].c_str();
}

////


ID Core_TimeAdd()
{
	CORE_TIME_PRECOND(-1);

	return Timers->TimeAdd();
}

void Core_TimesUpdate()
{
	CORE_TIME_PRECOND(_VOID);

	Timers->Update();
}


void Core_TimeSpeedSet(ID id, float speed)
{
	CORE_TIME_PRECOND(_VOID);

	Timers->TimeSpeedSet(id, speed);
}

float Core_TimeSpeedGet(ID id)
{
	CORE_TIME_PRECOND(0);

	return Timers->TimeSpeedGet(id);
}


void Core_TimeWorkingSet(ID id, bool working)
{
	CORE_TIME_PRECOND(_VOID);

	Timers->TimeWorkingSet(id, working);
}

bool Core_TimeWorkingGet(ID id)
{
	CORE_TIME_PRECOND(false);

	return Timers->TimeWorkingGet(id);
}


void Core_TimeUnixStartSet(ID id, int64_t start_time)
{
	CORE_TIME_PRECOND(_VOID);

	Timers->TimeUnixStartSet(id, start_time);
}

int64_t Core_TimeUnixStartGet(ID id)
{
	CORE_TIME_PRECOND(0);

	return Timers->TimeUnixStartGet(id);
}

int64_t Core_TimeUnixCurrGet(ID id)
{
	CORE_TIME_PRECOND(0);

	return Timers->TimeUnixCurrGet(id);
}


int64_t Core_TimeTotalMcsGet(ID id)
{
	CORE_TIME_PRECOND(0);

	return Timers->TimeTotalMcsGet(id);
}

int64_t Core_TimeTotalMcsGetU(ID id)
{
	CORE_TIME_PRECOND(0);

	return Timers->TimeTotalMcsGetU(id);
}