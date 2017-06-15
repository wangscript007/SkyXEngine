
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "animated.h"

#include <gcore/sxgcore.h>

#if !defined(DEF_STD_REPORT)
#define DEF_STD_REPORT
report_func reportf = def_report;
#endif

#define SA_PRECOND(ret) if(!g_mgr){reportf(-1, "%s - sxanim is not init", gen_msg_location);return ret;}

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

AnimationManager * g_mgr = NULL;

SX_LIB_API void SXAnim_0Create()
{
	if(g_mgr)
	{
		reportf(-1, "%s - sxanim double init", gen_msg_location);
		return;
	}
	g_mgr = new AnimationManager(SGCore_GetDXDevice());
}
SX_LIB_API void SXAnim_AKill()
{
	SA_PRECOND(_VOID);
	mem_delete(g_mgr);
}

SX_LIB_API void SXAnim_Update(int thread)
{
	SA_PRECOND(_VOID);
	g_mgr->Update(thread);
}
SX_LIB_API void SXAnim_UpdateSetThreadNum(int num)
{
	SA_PRECOND(_VOID);
	g_mgr->SetThreadNum(num);
}
SX_LIB_API void SXAnim_Sync()
{
	SA_PRECOND(_VOID);
	g_mgr->Sync();
}
SX_LIB_API void SXAnim_Render(ID for_id)
{
	SA_PRECOND(_VOID);
	g_mgr->Render(for_id);
}

SX_LIB_API IAnimPlayer * SXAnim_CreatePlayer(const char * mdl)
{
	SA_PRECOND(NULL);
	Animation * anim = new Animation(g_mgr);
	if(mdl)
	{
		anim->SetModel(mdl);
	}
	return(anim);
}

SX_LIB_API void SXAnim_ModelsComVisible(const ISXFrustum * frustum, const float3 * viewpos, ID id_arr)
{
	SA_PRECOND(_VOID);
	g_mgr->ComputeVis(frustum, viewpos, id_arr);
}

SX_LIB_API ID SXAnim_ModelsAddArrForCom()
{
	SA_PRECOND(-1);
	return(g_mgr->GetNextVisId());
}
SX_LIB_API void SXAnim_ModelsDelArrForCom(ID id_arr)
{
	SA_PRECOND(_VOID);
	g_mgr->FreeVisID(id_arr);
}

SX_LIB_API void SXAnim_Dbg_Set(report_func rf)
{
	reportf = rf;
}