
#include <managed_render/gdata.h>

void GData::InitAllMatrix()
{
	GData::MCamProj = SMMatrixPerspectiveFovLH(GData::ProjFov, GData::WinSize.x / GData::WinSize.y, GData::NearFar.x, GData::NearFar.y);
	GData::MLightProj = SMMatrixPerspectiveFovLH(GData::ProjFov, GData::WinSize.x / GData::WinSize.y, GData::NearFar.x, G_DATA_LIGHT_FAR);

	GData::MRefPlaneSkyProj = SMMatrixPerspectiveFovLH(GData::ProjFov, GData::WinSize.x / GData::WinSize.y, GData::NearFar.x, G_DATA_LIGHT_FAR);
	GData::MRefCubeSkyProj = SMMatrixPerspectiveFovLH(SM_PI * 0.5f, 1, GData::NearFar.x, G_DATA_LIGHT_FAR);

	Core_RMatrixSet(G_RI_MATRIX_OBSERVER_PROJ, &GData::MCamProj);
	Core_RMatrixSet(G_RI_MATRIX_LIGHT_PROJ, &GData::MLightProj);

	Core_RFloatSet(G_RI_FLOAT_OBSERVER_NEAR, GData::NearFar.x);
	Core_RFloatSet(G_RI_FLOAT_OBSERVER_FAR, GData::NearFar.y);
	Core_RFloatSet(G_RI_FLOAT_OBSERVER_FOV, GData::ProjFov);
}

void GData::Pathes::InitAllPathes()
{
	char tmppath[1024];
	GetModuleFileName(NULL, tmppath, 1024);
	int len = strlen(tmppath);
	while (tmppath[len--] != '\\')
	{
		if (tmppath[len - 1] == '\\')
		{
			len--;
			memcpy(GData::Pathes::ForExe, tmppath, len);
			GData::Pathes::ForExe[len] = 0;
		}
	}

	sprintf(GData::Pathes::WorkingTex, "%s%s", GData::Pathes::ForExe, "\\worktex\\");
	sprintf(GData::Pathes::GameSource, "%s%s", GData::Pathes::ForExe, "\\gamesource\\");
	sprintf(GData::Pathes::Screenshots, "%s%s", GData::Pathes::ForExe, "\\screenshots\\");
	sprintf(GData::Pathes::Configs, "%s%s", GData::Pathes::GameSource, "configs\\");
	sprintf(GData::Pathes::Levels, "%s%s", GData::Pathes::GameSource, "levels\\");
	sprintf(GData::Pathes::Meshes, "%s%s", GData::Pathes::GameSource, "meshes\\");
	sprintf(GData::Pathes::Models, "%s%s", GData::Pathes::GameSource, "models\\");
	sprintf(GData::Pathes::Shaders, "%s%s", GData::Pathes::GameSource, "shaders\\");
	sprintf(GData::Pathes::Sounds, "%s%s", GData::Pathes::GameSource, "sounds\\");
	sprintf(GData::Pathes::Scripts, "%s%s", GData::Pathes::GameSource, "scripts\\");

	sprintf(GData::Pathes::Textures, "%s%s", GData::Pathes::GameSource, "textures\\");
	sprintf(GData::Pathes::TexturesDetail, "%s%s", GData::Pathes::GameSource, "textures\\detail\\");
	sprintf(GData::Pathes::TexturesSkyBoxes, "%s%s", GData::Pathes::Textures, "sky\\");
	sprintf(GData::Pathes::Materials, "%s%s", GData::Pathes::GameSource, "materials\\");
	sprintf(GData::Pathes::GUIresources, "%s%s", GData::Pathes::GameSource, "resource\\");

	SetCurrentDirectoryA(GData::Pathes::GameSource);
}

void GData::IDsShaders::InitAllShaders()
{
	GData::IDsShaders::VS::ScreenOut = SGCore_ShaderLoad(ShaderType::st_vertex, "pp_quad_render.vs", "pp_quad_render", ShaderCheckDouble::scd_path);
	GData::IDsShaders::PS::ScreenOut = SGCore_ShaderLoad(ShaderType::st_pixel, "pp_quad_render.ps", "pp_quad_render", ShaderCheckDouble::scd_path);

	GData::IDsShaders::VS::ResPos = SGCore_ShaderLoad(ShaderType::st_vertex, "pp_quad_render_res_pos.vs", "pp_quad_render_res_pos", ShaderCheckDouble::scd_path);


	GData::IDsShaders::PS::ComLightingNonShadow = SGCore_ShaderLoad(ShaderType::st_pixel, "lighting_com.ps", "lighting_com_nonshadow", ShaderCheckDouble::scd_name);
	D3DXMACRO Defines_IS_SHADOWED[] = { { "IS_SHADOWED", "" }, { 0, 0 } };
	GData::IDsShaders::PS::ComLightingShadow = SGCore_ShaderLoad(ShaderType::st_pixel, "lighting_com.ps", "lighting_com_shadow", ShaderCheckDouble::scd_name, Defines_IS_SHADOWED);
	GData::IDsShaders::PS::BlendAmbientSpecDiffColor = SGCore_ShaderLoad(ShaderType::st_pixel, "lighting_blend.ps", "lighting_blend", ShaderCheckDouble::scd_path);

	GData::IDsShaders::PS::UnionAlpha = SGCore_ShaderLoad(ShaderType::st_pixel, "pp_union_alpha.ps", "pp_union_alpha", ShaderCheckDouble::scd_path);

	D3DXMACRO Defines_STR[] = { { "_STR_", "" }, { 0, 0 } };
	GData::IDsShaders::PS::StencilStr = SGCore_ShaderLoad(ShaderType::st_pixel, "pp_alpha_stencil_mark.ps", "pp_stencil_str", ShaderCheckDouble::scd_name, Defines_STR);
	D3DXMACRO Defines_COLUMN[] = { { "_COLUMN_", "" }, { 0, 0 } };
	GData::IDsShaders::PS::StencilColumn = SGCore_ShaderLoad(ShaderType::st_pixel, "pp_alpha_stencil_mark.ps", "pp_stencil_column", ShaderCheckDouble::scd_name, Defines_COLUMN);
	D3DXMACRO Defines_COLUMN_STR[] = { { "_COLUMN_STR_", "" }, { 0, 0 } };
	GData::IDsShaders::PS::StencilStrColumn = SGCore_ShaderLoad(ShaderType::st_pixel, "pp_alpha_stencil_mark.ps", "pp_stencil_str_column", ShaderCheckDouble::scd_name, Defines_COLUMN_STR);
}

LRESULT CALLBACK GData::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, message, wParam, lParam));
}

void GData::InitWin(const char* name, const char* caption)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GData::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(0);
	wcex.hIcon = NULL;
	wcex.hCursor = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = name;
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);

	RECT rc = { 0, 0, GData::WinSize.x, GData::WinSize.y };
	AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

	GData::Handle3D = CreateWindowEx(
		0,
		name,
		caption,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		0, 0,
		GetModuleHandle(0),
		0);
	
	if (GData::IsWindowed)
		ShowWindow(GData::Handle3D, SW_SHOW);
	else
		ShowWindow(GData::Handle3D, SW_MAXIMIZE);
}