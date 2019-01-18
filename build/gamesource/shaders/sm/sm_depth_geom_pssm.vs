
/*
sm_depth_geom_pssm.vs
Рендер глубины сцены (геометрии) с позиции позиции глобального источника света
*/

#include <../struct.h>
#include <../shadow.h>

//##########################################################################

half4x4 g_mWVP:register(c0);
half3 g_vLigthPos;

//##########################################################################

VSO_SceneCommon main(VSI_Geometry IN)
{
	VSO_SceneCommon OUT;

	OUT.vPosition = mul(half4(IN.vPosition.xyz, 1.0),g_mWVP);
	OUT.vTexUV = IN.vTexUV;
	OUT.vPos = OUT.vPosition;

	return OUT;
}