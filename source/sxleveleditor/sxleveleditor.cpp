
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define SX_LEVEL_EDITOR
#define SX_EXE

#define _CRT_SECURE_NO_WARNINGS

//#include <vld.h> 
#include <skyxengine.cpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	SkyXEngine_PreviewCreate();
	SXGUIRegClass::RegGroupBox();
	SXLevelEditor::InitAllElements();

	GData::Handle3D = SXLevelEditor::RenderWindow->GetHWND();
	GData::HandleParent3D = SXLevelEditor::JobWindow->GetHWND();
	RECT winrndrect;
	SXLevelEditor::RenderWindow->GetClientRect(&winrndrect);

	GData::WinSize.x = winrndrect.right;
	GData::WinSize.y = winrndrect.bottom;

	SkyXEngine_Init();

	IDirect3DTexture9* SelectMaterial;
	GData::DXDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &SelectMaterial, NULL);
	D3DLOCKED_RECT LockedRect;
	uint32_t tmpColor = D3DCOLOR_ARGB(255, 255, 0, 255);

	SelectMaterial->LockRect(0, &LockedRect, 0, 0);

	uint32_t* tmpOldColor = (uint32_t*)LockedRect.pBits + 0 * LockedRect.Pitch + 0 * sizeof(uint32_t);
	memcpy(tmpOldColor, &tmpColor, sizeof(uint32_t));

	SelectMaterial->UnlockRect(0);

	SGCore_LoadTexLoadTextures();
	GData::IDSelectTex = SGCore_LoadTexCreate("select_material__", SelectMaterial);

	SGCore_LoadTexStdPath(GData::Pathes::Textures);
	SGCore_LoadTexLoadTextures();

	int countgc = SXGame_EntGetClassListCount();
	const char** listgc = new const char*[countgc];

	SXGame_EntGetClassList(listgc, countgc);
	for (int i = 0; i < countgc; ++i)
	{
		SXLevelEditor::ComboBoxGameClass->AddItem(listgc[i]);
	}
	mem_delete_a(listgc);


	SkyXEngine_PreviewKill();
	SXLevelEditor::JobWindow->Visible(true);
	int result = SkyXEngine_CycleMain();
	SkyXEngine_Kill();
	return result;
}