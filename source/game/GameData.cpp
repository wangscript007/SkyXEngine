
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "GameData.h"
#include "CrosshairManager.h"

#include "Ragdoll.h"

#include <score/sxscore.h>

#include "Tracer.h"


CPlayer * GameData::m_pPlayer;
CPointCamera * GameData::m_pActiveCamera;
CEntityManager * GameData::m_pMgr;

CRagdoll * g_pRagdoll;
IAnimPlayer * pl;

CTracer *g_pTracer;

GameData::GameData()
{
	loadFoostepsSounds();

	m_pMgr = new CEntityManager();

	Core_0RegisterConcmd("+forward", ccmd_forward_on);
	Core_0RegisterConcmd("-forward", ccmd_forward_off);
	Core_0RegisterConcmd("+backward", ccmd_backward_on);
	Core_0RegisterConcmd("-backward", ccmd_backward_off);
	Core_0RegisterConcmd("+left", ccmd_left_on);
	Core_0RegisterConcmd("-left", ccmd_left_off);
	Core_0RegisterConcmd("+right", ccmd_right_on);
	Core_0RegisterConcmd("-right", ccmd_right_off);
	Core_0RegisterConcmd("+boost", ccmd_boost_on);
	Core_0RegisterConcmd("-boost", ccmd_boost_off);
	Core_0RegisterConcmd("+crouch", ccmd_crouch_on);
	Core_0RegisterConcmd("-crouch", ccmd_crouch_off);
	Core_0RegisterConcmd("+jump", ccmd_jump_on);
	Core_0RegisterConcmd("-jump", ccmd_jump_off);
	Core_0RegisterConcmd("+crawl", ccmd_crawl_on);
	Core_0RegisterConcmd("-crawl", ccmd_crawl_off);
	Core_0RegisterConcmd("+attack", ccmd_attack_on);
	Core_0RegisterConcmd("-attack", ccmd_attack_off);
	Core_0RegisterConcmd("+attack2", ccmd_attack2_on);
	Core_0RegisterConcmd("-attack2", ccmd_attack2_off);
	Core_0RegisterConcmd("reload", ccmd_reload);
	Core_0RegisterConcmd("switch_firemode", ccmd_switch_firemode);
	Core_0RegisterConcmd("flashlight", ccmd_toggleflashlight);

	Core_0RegisterConcmd("spawn", ccmd_spawn);
	Core_0RegisterConcmd("observe", ccmd_observe);

	//Core_0RegisterCVarFloat("r_default_fov", 45.0f, "Default FOV value");
	Core_0RegisterCVarBool("cl_mode_editor", false, "Editor control mode");
	Core_0RegisterCVarBool("cl_grab_cursor", true, "Grab cursor on move");
	

	Core_0RegisterCVarBool("cl_bob", true, "View bobbing");
	Core_0RegisterCVarFloat("cl_bob_walk_y", 0.1f, "View bobbing walk y amplitude");
	Core_0RegisterCVarFloat("cl_bob_walk_x", 0.1f, "View bobbing walk strafe amplitude");
	Core_0RegisterCVarFloat("cl_bob_run_y", 0.2f, "View bobbing run y amplitude");
	Core_0RegisterCVarFloat("cl_bob_run_x", 0.15f, "View bobbing run strafe amplitude");
	Core_0RegisterCVarFloat("cl_bob_walk", 0.5f, "View bobbing walk period");
	Core_0RegisterCVarFloat("cl_bob_run", 1.0f, "View bobbing run period");

	CCrosshairManager::loadConfig("config/game/crosshairs.cfg");

	m_pPlayer = (CPlayer*)CREATE_ENTITY("player", m_pMgr);
	m_pActiveCamera = m_pPlayer->getCamera();
	m_pCrosshair = m_pPlayer->getCrosshair();

	ID idCrosshairDefault = CCrosshairManager::getCrosshairID("default");
	if(ID_VALID(idCrosshairDefault))
	{
		CCrosshairManager::loadCrosshair(idCrosshairDefault, m_pCrosshair);
	}

	Core_0RegisterConcmdClsArg("+debug_slot_move", m_pPlayer, (SXCONCMDCLSARG)&CPlayer::_ccmd_slot_on);
	Core_0RegisterConcmdCls("-debug_slot_move", m_pPlayer, (SXCONCMDCLS)&CPlayer::_ccmd_slot_off);

	g_pTracer = new CTracer(5000);

	//m_pPlayer->setModel("models/stalker_zombi/stalker_zombi_a.dse");
	//m_pPlayer->playAnimation("reload");

	//pl = SXAnim_CreatePlayer("models/stalker_zombi/stalker_zombi_a.dse");
	//pl->setPos(float3(0, 0, 0));
	//g_pRagdoll = new CRagdoll(pl);
	//pl->setRagdoll(g_pRagdoll);
}
GameData::~GameData()
{
	//mem_delete(g_pRagdoll);

	mem_delete(g_pTracer);
	mem_delete(m_pMgr);

	for(int i = 0; i < MPT_COUNT; ++i)
	{
		// @TODO: SSCore_SndDelete3dInst()
		mem_delete_a(m_pidFootstepSound[i]);
	}
}

void GameData::update()
{
	m_pCrosshair->update();
}
void GameData::render()
{
	//g_pTracer->render();
}
void GameData::renderHUD()
{
	m_pCrosshair->render();
}
void GameData::sync()
{
	m_pCrosshair->onSync();
}

void GameData::playFootstepSound(MTLTYPE_PHYSIC mtl_type, const float3 &f3Pos)
{
	int iCount = m_iFootstepSoundCount[mtl_type];
	if(!iCount)
	{
		return;
	}
	ID idSound = m_pidFootstepSound[mtl_type][rand() % iCount];
	SSCore_SndInstancePlay3d(idSound, (float3*)&f3Pos);
}

void GameData::loadFoostepsSounds()
{
	Array<const char*> aSounds[MPT_COUNT];

	aSounds[MTLTYPE_PHYSIC_CONCRETE].push_back("actor/step/default1.ogg");
	aSounds[MTLTYPE_PHYSIC_CONCRETE].push_back("actor/step/default2.ogg");
	aSounds[MTLTYPE_PHYSIC_CONCRETE].push_back("actor/step/default3.ogg");
	aSounds[MTLTYPE_PHYSIC_CONCRETE].push_back("actor/step/default4.ogg");

	aSounds[MTLTYPE_PHYSIC_METAL].push_back("actor/step/metal_plate1.ogg");
	aSounds[MTLTYPE_PHYSIC_METAL].push_back("actor/step/metal_plate2.ogg");
	aSounds[MTLTYPE_PHYSIC_METAL].push_back("actor/step/metal_plate3.ogg");
	aSounds[MTLTYPE_PHYSIC_METAL].push_back("actor/step/metal_plate4.ogg");

	aSounds[MTLTYPE_PHYSIC_TREE].push_back("actor/step/new_wood1.ogg");
	aSounds[MTLTYPE_PHYSIC_TREE].push_back("actor/step/new_wood2.ogg");
	aSounds[MTLTYPE_PHYSIC_TREE].push_back("actor/step/new_wood3.ogg");
	aSounds[MTLTYPE_PHYSIC_TREE].push_back("actor/step/new_wood4.ogg");

	aSounds[MTLTYPE_PHYSIC_GROUD_SAND].push_back("actor/step/earth1.ogg");
	aSounds[MTLTYPE_PHYSIC_GROUD_SAND].push_back("actor/step/earth2.ogg");
	aSounds[MTLTYPE_PHYSIC_GROUD_SAND].push_back("actor/step/earth3.ogg");
	aSounds[MTLTYPE_PHYSIC_GROUD_SAND].push_back("actor/step/earth4.ogg");

	aSounds[MTLTYPE_PHYSIC_WATER].push_back("actor/step/t_water1.ogg");
	aSounds[MTLTYPE_PHYSIC_WATER].push_back("actor/step/t_water2.ogg");

	aSounds[MTLTYPE_PHYSIC_LEAF_GRASS].push_back("actor/step/grass1.ogg");
	aSounds[MTLTYPE_PHYSIC_LEAF_GRASS].push_back("actor/step/grass2.ogg");
	aSounds[MTLTYPE_PHYSIC_LEAF_GRASS].push_back("actor/step/grass3.ogg");
	aSounds[MTLTYPE_PHYSIC_LEAF_GRASS].push_back("actor/step/grass4.ogg");

	//aSounds[MTLTYPE_PHYSIC_GLASS].push_back("actor/step/.ogg");
	//aSounds[MTLTYPE_PHYSIC_PLASTIC].push_back("actor/step/.ogg");
	//aSounds[MTLTYPE_PHYSIC_FLESH].push_back("actor/step/.ogg");

	for(int i = 0; i < MPT_COUNT; ++i)
	{
		Array<const char*> *paSounds = &aSounds[i];
		int jl = paSounds->size();
		m_iFootstepSoundCount[i] = jl;
		m_pidFootstepSound[i] = jl ? new ID[jl] : NULL;
		for(int j = 0; j < jl; ++j)
		{
			m_pidFootstepSound[i][j] = SSCore_SndCreate3dInst(paSounds[0][j], false, 0, 100);
		}
	}
}

//###################################################################

void GameData::ccmd_forward_on()
{
	m_pPlayer->move(PM_FORWARD, TRUE);
}
void GameData::ccmd_forward_off()
{
	m_pPlayer->move(PM_FORWARD, FALSE);
}

void GameData::ccmd_backward_on()
{
	m_pPlayer->move(PM_BACKWARD, TRUE);
}
void GameData::ccmd_backward_off()
{
	m_pPlayer->move(PM_BACKWARD, FALSE);
}

void GameData::ccmd_left_on()
{
	m_pPlayer->move(PM_LEFT, TRUE);
}
void GameData::ccmd_left_off()
{
	m_pPlayer->move(PM_LEFT, FALSE);
}

void GameData::ccmd_right_on()
{
	m_pPlayer->move(PM_RIGHT, TRUE);
}
void GameData::ccmd_right_off()
{
	m_pPlayer->move(PM_RIGHT, FALSE);
}

void GameData::ccmd_boost_on()
{
	m_pPlayer->move(PM_RUN, TRUE);
}
void GameData::ccmd_boost_off()
{
	m_pPlayer->move(PM_RUN, FALSE);
}

void GameData::ccmd_crouch_on()
{
	m_pPlayer->move(PM_CROUCH, TRUE);
}
void GameData::ccmd_crouch_off()
{
	m_pPlayer->move(PM_CROUCH, FALSE);
}

void GameData::ccmd_crawl_on()
{
	m_pPlayer->move(PM_CRAWL, TRUE);
}
void GameData::ccmd_crawl_off()
{
	m_pPlayer->move(PM_CRAWL, FALSE);
}

void GameData::ccmd_jump_on()
{
	m_pPlayer->move(PM_JUMP, TRUE);
}
void GameData::ccmd_jump_off()
{
	m_pPlayer->move(PM_JUMP, FALSE);
}

void GameData::ccmd_attack_on()
{
	m_pPlayer->attack(TRUE);
}
void GameData::ccmd_attack_off()
{
	m_pPlayer->attack(FALSE);
}

void GameData::ccmd_attack2_on()
{
	m_pPlayer->attack2(TRUE);
}
void GameData::ccmd_attack2_off()
{
	m_pPlayer->attack2(FALSE);
}

void GameData::ccmd_spawn()
{
	Core_0ConsoleExecCmd("cl_mode_editor 0");
	m_pPlayer->spawn();
}
void GameData::ccmd_observe()
{
	m_pPlayer->observe();
}

void GameData::ccmd_reload()
{
	m_pPlayer->reload();
}

void GameData::ccmd_toggleflashlight()
{
	m_pPlayer->toggleFlashlight();
}

void GameData::ccmd_switch_firemode()
{
	m_pPlayer->nextFireMode();
}
