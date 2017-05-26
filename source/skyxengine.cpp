
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define _CRT_SECURE_NO_WARNINGS
#pragma once

#define SX_EXE
#define SX_GAME

#include <SkyXEngine.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	InitOutLog();
	srand((unsigned int)time(0));

	GData::InitWin("SkyXEngine", "SkyXEngine");

	SkyXEngine_Init();

	SGCore_SkyBoxLoadTex("sky_2_cube.dds");
	SGCore_SkyCloudsLoadTex("sky_oblaka.dds");
	SGCore_SkyCloudsSetWidthHeightPos(2000, 2000, &float3(0, 0, 0));

	Level::Load("stalker_atp");
	SXPhysics_LoadGeom();

	SGeom_0SettGreenSetFreqGrass(30);

	IAnimPlayer * pl;
	pl = SXAnim_CreatePlayer("models/stalker_zombi/stalker_zombi_a.dse");
	pl->SetPos(float3(-17.18, -1.38f, -32.3));
	pl->Play("reload");

	//TestEffect = new Effect();

	/*ParticlesData data;
	ZeroMemory(&data, sizeof(ParticlesData));

	data.FigureType = ParticlesFigureType::pft_quad_composite;
	data.FigureCountQuads = 4;
	data.FigureRotRand = false;
	data.FigureTapY = true;

	data.ReCreateCount = -1;*/

	//data.SpawnNextTime = 1000;
	//data.Billboard = true;

	//data.TimeLife = 100000;
	//data.TimeLifeDisp = 200;

	//data.AlphaAgeDepend = ParticlesDependType::padt_direct;

	/*data.SizeParticle = float2(0.3, 0.3);
	data.SizeDisp = 0.3;*/
	//data.SizeDependAge = ParticlesDependType::padt_direct;

	/*data.Velocity = float3(0.01, 0.1, 0.01);
	data.VelocityDisp = 0.1;
	data.VelocityDispXNeg = true;
	data.VelocityDispYNeg = false;
	data.VelocityDispZNeg = true;*/

	/*data.AnimTexCountCadrsX = 11;
	data.AnimTexCountCadrsY = 7;
	data.AnimTexRate = 10;
	data.AnimTexStartCadr = 1;*/
	//data.AnimTexStartCadrDisp = 20;

	/*data.CharacterCircle = true;
	data.CharacterCircleAngle = 0.5;*/

	/*data.CharacterRotate = true;
	data.CharacterRotateAngle = 0.1;*/
	//data.CharacterRotateAngleDisp = 0.2;
	//data.CharacterRotateAngleDispNeg = true;

	/*data.CharacterDeviation = true;
	data.CharacterMotionAmplitude = 0.01f;
	data.CharacterMotionCoefAngle = 100.0;*/

	/*data.CharacterDeviationAmplitude = 0.02f;
	data.CharacterDeviationCoefAngle = 100.0;

	data.CharacterDeviationDisp = 0.1;
	data.CharacterDeviationDispNeg = true;

	data.CharacterDeviationCountDelayMls = 100;
	data.CharacterDeviationType = ParticlesDeviationType::pdt_rnd;
	data.CharacterDeviationAxis = ParticlesAxis::pa_y;
	data.CharacterDeviationTapX = true;
	data.CharacterDeviationTapZ = true;*/

	//data.Lighting = true;

	/*ID tmpeffid = SPE_EffectAdd("test");
	ID tmppartid = SPE_ParticlesAdd(tmpeffid, &data);

	//ID idtex = SGCore_LoadTexAddName("pfx_explotions_2.dds", LoadTexType::ltt_load);
	SGCore_LoadTexLoadTextures();
	SPE_ParticlesTextureSet(tmpeffid, tmppartid, idtex);
	SPE_ParticlesCreate(tmpeffid, tmppartid, 1);

	SPE_ParticlesSet(tmpeffid, tmppartid, SizeParticle, float2_t(2, 2));
	SPE_ParticlesSet(tmpeffid, tmppartid, TransparencyCoef, 0.25);*/
	//SPE_ParticlesSet(tmpeffid, tmppartid, FigureCountQuads, 10);
	//SPE_ParticlesSet(tmpeffid, tmppartid, FigureRotRand, true);
	//SPE_ParticlesSet(tmpeffid, tmppartid, FigureTapX, true);
	//SPE_ParticlesSet(tmpeffid, tmppartid, FigureTapZ, true);
	
	/*SGeom_ModelsAddModel("stalker_atp.dse", 0, "stalker_atp.dse");

	SGeom_GreenAddGreen("tree_topol", "terrain_mp_atp_mask_tree.dds", 0.3, "green\\tree_topol_lod0.dse", "green\\tree_topol_lod1.dse", "green\\tree_topol_lod2.dse", "green\\tree_topol_lod2.dse");
	SGeom_GreenAddGreen("trava_green_det2", "terrain_mp_atp_mask_grass.dds", 0.2, "green\\trava_green_det2.dse", 0, 0, 0);


	SML_LigthsCreatePoint(
		&float3(60,60,0),
		LIGHTS_GLOBAL_MAX_POWER,
		LIGHTS_GLOBAL_STD_RADIUS,
		&float3(1,1,1),
		true,
		true);
		SML_LigthsSetEnable(SML_LigthsGetCount() - 1, true);
		SML_LigthsSetName(SML_LigthsGetCount() - 1, "sun");
		
	Level::Save("stalker_atp"); */

	char tmppathexe[1024];
	char tmppath[1024];
	GetModuleFileName(NULL, tmppath, 1024);
	int len = strlen(tmppath);
	while (tmppath[len--] != '\\')
	{
		if (tmppath[len - 1] == '\\')
		{
			len--;
			memcpy(tmppathexe, tmppath, len);
			tmppathexe[len] = 0;
		}
	}

	SGCore_LoadTexStdPath(GData::Pathes::Textures);
	SGCore_LoadTexLoadTextures();

	ID tmpid = SSCore_SndCreate3d("Exclusion_zone.ogg", false, 0, 100, 0.1);
	if(tmpid >= 0)
	{
		SSCore_SndPosCurrSet(tmpid, 20, SOUND_POS_SEC);
		SSCore_SndPlay(tmpid);
		//ms->SoundPanSet(tmpid, DSBPAN_RIGHT, 0);
		//ms->SoundVolumeSet(tmpid, 100);
	}

	ID tmpid2 = SSCore_SndCreate2d("battle_1.ogg", true, 0);
	if(tmpid2 >= 0)
	{
		//SSCore_SndVolumeSet(tmpid2, 50, SOUND_VOL_PCT);
		SSCore_SndPlay(tmpid2);
	}

	//ms->SoundEffectGargleSet(tmpid, 100, DSFXGARGLE_WAVE_SQUARE);

	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static DWORD lastTime = GetTickCount();
	static DWORD TimeCCadr = 0;

	while (msg.message != WM_QUIT && IsWindow(GData::Handle3D))
	{
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			static DWORD TimeStart = 0;
			DWORD TimeThis = GetTickCount();

			DWORD currTime = GetTickCount();
			DWORD timeDelta = (currTime - lastTime);

			Core_0ConsoleUpdate();
#ifdef SX_GAME
			GData::ObjCamera = SXGame_GetActiveCamera();
#endif
			if (GetActiveWindow() == GData::Handle3D)
			{
				SGCore_LoadTexLoadTextures();
				SXRenderFunc::MainRender(timeDelta);
			}

			TimeCCadr = timeDelta;
			TimeStart = TimeThis;

			lastTime = currTime;
		}
	}

	/*
	SXGame_0Kill();
	SXPhysics_0Kill();
	SXAnim_0Kill();
	mem_release(GData::ObjCamera);
	SGeom_0CreateKill();
	SML_0Kill();
	SGCore_0Kill();
	Core_AKill();*/

	SkyXEngine_Kill();

	return msg.wParam;
}