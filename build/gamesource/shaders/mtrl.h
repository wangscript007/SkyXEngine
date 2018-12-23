
/*
mtrl.h
Общие функции для материалов
*/
 
//! матрица для трансформации координат текстуры отражения (над водой)
static const half4x4  MatrixReflection =
{	0.5,	0,		0,		0, 
    0,		0.5,	0,		0, 
    0,		0,		0.5,	0, 
    0.5,	0.5,	0.5,	1
};

//! матрица для трансофрмации координат текстуры преломления (под водой)
static const half4x4  MatrixRefraction =
{	0.5,	0,		0,		0, 
    0,		-0.5,	0,		0, 
    0,		0,		0.5,	0, 
    0.5,	0.5,	0.5,	1
};

//##########################################################################

//! отсечение пикселя по дистанции (при превышении)
void ClipFar(half fZ, half fFar)
{
	clip(fFar-fZ);
}

//##########################################################################

//! просчет цвета линейной глубины [0,1] на основании текущей позиции и плоскостей отсечения! 
half ComDepthByPos(half4 vPositionWVP, half2 vNearFar)
{
	return ((vPositionWVP.z + vNearFar.x)/vNearFar.y);
}

//! аналогично #ComDepthByPos, только возвращает вектор
half4 ComDepthByPosVec4(half4 vPositionWVP, half2 vNearFar)
{
	half fDepth = ComDepthByPos(vPositionWVP, vNearFar);
	return half4(fDepth, fDepth, fDepth,1);
}

#define GetDepthW ComDepthByPosVec4

//##########################################################################

//! возвращает номер лода для для отражений, на основании шероховатости материала [0, 1]
half GetTexLod4Ref(half fRoughness)
{
	return lerp(0.f, MTRL_REF_LOD_COUNT, fRoughness);
}

/*! возаращет нужный лод текстуры,
 \param fCountLods - количество лодов в текстуре
 \param vDX - ddx(vTexUV.x)
 \param vDY - ddx(vTexUV.y)
*/
half GetTextureLodEx(half fCountLods, half2 vDX, half2 vDY)
{
	return (fCountLods - 1.0)+log2(max(length(vDX), length(vDY)));
}

//! возвращает номер лода, подробности #GetTextureLodEx
half GetTextureLod(half fCountLods, half2 vTexUV)
{
	return GetTextureLodEx(fCountLods, ddx(vTexUV.x), ddx(vTexUV.y));
}

//! возвращает номер нужного лода на основании текстурных координат, для текстур сцены (текстуры для моделей)
half GetTextureLod4Scene(half2 vTexUV)
{
	return GetTextureLodEx(SCENE_COUNT_TEXTURE_LOD, ddx(vTexUV), ddy(vTexUV));
}

//##########################################################################

//! кодирование xyz нормали в xy
half3 NormalEncode(half3 vNormal)
{
	/*vNormal.xy = vNormal.xy * 0.5 + 0.5;
	
	[branch]if(vNormal.z >= 0.0)
		vNormal.z = 0.5 + fLayer * g_fUnit256;
	else
		vNormal.z = fLayer * g_fUnit256;*/
	
	return vNormal * 0.5 + 0.5;
}

//! декодирование нормали xy в xyz
half3 NormalDecode(half3 vNormal)
{
	/*half fLayer = 0;
	
	if(vNormal.z >= 0.5)
		fLayer = (floor((vNormal.z - 0.5) * 255.0 + 0.5)) * g_fUnit256;
	else
		fLayer = floor(vNormal.z * 255.0 + 0.5) * g_fUnit256;
	
	vNormal.xy = vNormal.xy * 2.0 - 1.0;
	vNormal.z = sign(vNormal.z * 2.0 - 1.0);
	vNormal.z = sqrt(1 - pow(vNormal.x, 2) - pow(vNormal.y, 2)) * vNormal.z;
	
	return half4(vNormal, fLayer);*/
	
	return vNormal * 2.0 - 1.0;
}

half LayerEncode(half fLayer, int iLighted)
{
	half fResult = 0;
	[branch]if(iLighted == MTLTYPE_LIGHT)
		fResult = 0.5 + fLayer * g_fUnit256;
	else
		fResult = fLayer * g_fUnit256;
	
	return fResult;
}


half2 LayerDecode(half fCode)
{
	half fLayer = 0;
	int iLighted = MTLTYPE_UNLIT;
	
	if(fCode >= 0.5)
	{
		fLayer = /*fCode - 0.5;//*/(floor((fCode - 0.5) * 255.0 + 0.5)) * g_fUnit256;
		iLighted = MTLTYPE_LIGHT;
	}
	else
	{
		fLayer = /*fCode;//*/floor(fCode * 255.0 + 0.5) * g_fUnit256;
		iLighted = MTLTYPE_UNLIT;
	}
	
	return half2(int(fLayer * LAYERS_COUNT_MAX), iLighted);
}

#define LayerDecodeLayer(fCode)(LayerDecode(fCode).x)
#define LayerDecodeType(fCode)(LayerDecode(fCode).y)

//! преобразвоание цвета в нормаль (если конечно цвет содержит нормаль)
half3 Color2Normal(half3 vColor)
{
	return (2.0 * vColor - 1.0);
}

//##########################################################################

/*! формирование структуры G буфера
 \param vColor - float4 цвет 
 \param vNormal - float3 нормаль 
 \param vParam - float4 параметры освещения (из текстуры парамтеров) 
 \param vWVPposition - float4 позиция пикселя (считается в вершинном шейдере как mul(vPos, g_mWVP))
 \param vNearFarLayers - float4, аналог g_vNearFarLayers (https://wiki.skyxengine.com/index.php?title=Организация_шейдеров_материалов#Константы) 
*/
PSO_Gbuffer CreateGbuffer(half4 vColor, half3 vNormal, half4 vParam, half4 vWVPposition, half4 vNearFarLayers)
{
	PSO_Gbuffer OUT;
	
	OUT.vColor = vColor;
	
	/*vNormal = normalize(vNormal);
	OUT.vNormal.xyz = NormalEncode(vNormal, vNearFarLayers.w);
	OUT.vNormal.w = vNearFarLayers.z;*/
	
	vNormal = normalize(vNormal);
	OUT.vNormal.xyz = NormalEncode(vNormal);
	OUT.vNormal.w = LayerEncode(vNearFarLayers.w, vNearFarLayers.z);
	
	OUT.vParam = vParam;
	
	OUT.vDepth = ComDepthByPosVec4(vWVPposition,vNearFarLayers.xy);
	
	return OUT;
}

//##########################################################################

//! возвращает фактор интерполяции [0, 1] для детальных/микрорельефных текстур, где чем меньше значение тем больше будет проявление детальности/микронормалей
half GetLerpFactorDetail(half fDistance)
{
	return saturate(fDistance/MTRL_LAND_DIST);
}

//! смешивание макронормали (модели) с микронормалью (из normal map)
half3 MixNormalMicro(half3 vMacroNormal, half3 vMicroNormal)
{
	return normalize((vMacroNormal + half3(vMicroNormal.xy,vMacroNormal.z)));
}

//! смешивание 2 детальных текстур по маске, где r канал маски для первой детальной текстуры, а g для второй
half4 MixDetail2(half4 vMask, half4 vDetail1, half4 vDetail2, half fIntesity)
{
	return (vDetail1 * vMask.r + vDetail2 * vMask.g) * fIntesity * 2.0;
}

//! смешивание 4 детальных текстур по маске, где на каждую текстуру по каналу из маски, r канал для первой детальной, и т.д.
half4 MixDetail4(half4 vMask, half4 vDetail1, half4 vDetail2, half4 vDetail3, half4 vDetail4, half fIntesity)
{
	return (vDetail1 * vMask.r + vDetail2 * vMask.g + vDetail3 * vMask.b + vDetail4 * vMask.a) * fIntesity;
}

//! смешивание двух микронормалей (normal map)
half3 MixMicroNormal(half3 vMicroNormal1, half3 vMicroNormal2, half fIntesity)
{
	return (vMicroNormal1 * fIntesity + vMicroNormal2 * fIntesity);
}

//! смешивание 4 микронормалей (normal map) по маске, где на каждую текстуру по каналу из маски, r канал для vMicroNormal1, и т.д.
half3 MixMicroNormal4(half4 vMask, half3 vMicroNormal1, half3 vMicroNormal2, half3 vMicroNormal3, half3 vMicroNormal4, half fIntesity)
{
	return (vMicroNormal1 * vMask.r + vMicroNormal2 * vMask.g + vMicroNormal3 * vMask.b + vMicroNormal4 * vMask.a) * fIntesity;
}

//! смешивание цвета и детального цвета, на основе фактора интерполяции #GetLerpFactorDetail
half4 MixColorDetail(half4 vColor, half4 vDetail, half fLerpFactor)
{
	half4 vBlend = vColor * vDetail * (2.0 - vDetail);
	vColor.rgb = lerp(vBlend,vColor,fLerpFactor).rgb;
	return vColor;
}
