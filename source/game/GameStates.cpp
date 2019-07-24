#include "GameStates.h"

#include "GameData.h"

#include <score/sxscore.h>
#include <input/sxinput.h>


CMainMenuGameState::CMainMenuGameState()
{
	m_pDesktop = GameData::m_pGUI->createDesktopA("menu_main", "menu/main.html");

	gui::dom::IDOMnode *pNode = m_pDesktop->getDocument()->getElementById(L"engine_version");
	static const char **pszVersion = GET_PCVAR_STRING("engine_version");
	if(pNode && pszVersion)
	{
		pNode->setText(StringW(L"SkyXEngine ") + StringW(String(*pszVersion)), TRUE);
	}
}

CMainMenuGameState::~CMainMenuGameState()
{
	m_pDesktop->release();
}

void CMainMenuGameState::activate()
{
	GameData::m_pGUI->setActiveDesktop(m_pDesktop);
}

//##########################################################################

CIngameMenuGameState::CIngameMenuGameState()
{
	m_pDesktop = GameData::m_pGUI->createDesktopA("menu_ingame", "menu/ingame.html");

	gui::dom::IDOMnode *pNode = m_pDesktop->getDocument()->getElementById(L"engine_version");
	static const char **pszVersion = GET_PCVAR_STRING("engine_version");
	if(pNode && pszVersion)
	{
		pNode->setText(StringW(L"SkyXEngine ") + StringW(String(*pszVersion)), TRUE);
	}
}

CIngameMenuGameState::~CIngameMenuGameState()
{
	m_pDesktop->release();
}

void CIngameMenuGameState::activate()
{
	GameData::m_pGUI->setActiveDesktop(m_pDesktop);
}

//##########################################################################

void CIngameGameState::activate()
{
	Core_0ConsoleExecCmd("cl_grab_cursor 1");
	GameData::m_pHUDcontroller->activate();

	ID idTimerRender = Core_RIntGet(G_RI_INT_TIMER_GAME);
	Core_TimeWorkingSet(idTimerRender, true);
	SSCore_ChannelPlay(SX_SOUND_CHANNEL_GAME);
	SSInput_SetEnable(true);
	SPhysics_EnableSimulation();
}

void CIngameGameState::deactivate()
{
	ID idTimerRender = Core_RIntGet(G_RI_INT_TIMER_GAME);
	Core_TimeWorkingSet(idTimerRender, false);
	SSCore_ChannelStop(SX_SOUND_CHANNEL_GAME);
	SSInput_SetEnable(false);
	SPhysics_DisableSimulation();
}

//##########################################################################

void CEditorState::activate()
{
	ID idTimerRender = Core_RIntGet(G_RI_INT_TIMER_GAME);
	Core_TimeWorkingSet(idTimerRender, true);
	//SSCore_ChannelPlay(SX_SOUND_CHANNEL_GAME);
//	SSInput_SetEnable(true);

	GameData::m_pMgr->setEditorMode(true);
}

void CEditorState::deactivate()
{
	GameData::m_pMgr->setEditorMode(false);

	ID idTimerRender = Core_RIntGet(G_RI_INT_TIMER_GAME);
	Core_TimeWorkingSet(idTimerRender, false);
	//SSCore_ChannelStop(SX_SOUND_CHANNEL_GAME);
//	SSInput_SetEnable(false);
}

