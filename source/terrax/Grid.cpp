#include "Grid.h"


CGrid::CGrid(UINT uSize)
{
	assert(uSize);

	m_pDevice = SGCore_GetDXDevice();

	float fSize = (float)uSize * 0.5f;
	UINT uVC = (uSize * 100 + 1) * 4;
	IGXVertexBuffer *pVB = m_pDevice->createVertexBuffer(sizeof(vertex) * uVC, GX_BUFFER_USAGE_STATIC | GX_BUFFER_WRITEONLY);
	vertex *pVertices;
	UINT uCurV = 0;
	if(pVB->lock((void**)&pVertices, GXBL_WRITE))
	{
		pVertices[uCurV++] = {float3_t(-fSize, 0.0f, 0.0f)};
		pVertices[uCurV++] = {float3_t(fSize, 0.0f, 0.0f)};
		pVertices[uCurV++] = {float3_t(0.0f, 0.0f, -fSize)};
		pVertices[uCurV++] = {float3_t(0.0f, 0.0f, fSize)};
		m_uVertexPerStep[GRID_STEP_AXES] = {0, uCurV};

		for(UINT i = 0; i <= uSize; i += 100)
		{
			if(i * 2 == uSize)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_100M] = {m_uVertexPerStep[GRID_STEP_100M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize; i += 50)
		{
			if(i % 100 == 0)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_50M] = {m_uVertexPerStep[GRID_STEP_50M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize; i += 20)
		{
			if(i % 50 == 0)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_20M] = {m_uVertexPerStep[GRID_STEP_20M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize; i += 10)
		{
			if(i % 20 == 0 || i % 50 == 0)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_10M] = {m_uVertexPerStep[GRID_STEP_10M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize; i += 5)
		{
			if(i % 10 == 0)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_5M] = {m_uVertexPerStep[GRID_STEP_5M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize; i += 2)
		{
			if(i % 5 == 0)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_2M] = {m_uVertexPerStep[GRID_STEP_2M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize; ++i)
		{
			if(i % 2 == 0 || i % 5 == 0)
			{
				continue;
			}
			float f = (float)i - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_1M] = {m_uVertexPerStep[GRID_STEP_1M + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize * 2; ++i)
		{
			if(i % 2 == 0)
			{
				continue;
			}
			float f = (float)i * 0.5f - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_50CM] = {m_uVertexPerStep[GRID_STEP_50CM + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize * 5; ++i)
		{
			if(i % 5 == 0)
			{
				continue;
			}
			float f = (float)i * 0.2f - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_20CM] = {m_uVertexPerStep[GRID_STEP_20CM + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize * 10; ++i)
		{
			if(i % 2 == 0 || i % 5 == 0)
			{
				continue;
			}
			float f = (float)i * 0.1f - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_10CM] = {m_uVertexPerStep[GRID_STEP_10CM + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize * 20; ++i)
		{
			if(i % 2 == 0)
			{
				continue;
			}
			float f = (float)i * 0.05f - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_5CM] = {m_uVertexPerStep[GRID_STEP_5CM + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize * 50; ++i)
		{
			if(i % 5 == 0)
			{
				continue;
			}
			float f = (float)i * 0.02f - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_2CM] = {m_uVertexPerStep[GRID_STEP_2CM + 1].m_uEndVertex, uCurV};

		for(UINT i = 0; i < uSize * 100; ++i)
		{
			if(i % 2 == 0 || i % 5 == 0)
			{
				continue;
			}
			float f = (float)i * 0.01f - fSize;
			pVertices[uCurV++] = {float3_t(-fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(fSize, 0.0f, f)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, -fSize)};
			pVertices[uCurV++] = {float3_t(f, 0.0f, fSize)};
		}
		m_uVertexPerStep[GRID_STEP_1CM] = {m_uVertexPerStep[GRID_STEP_1CM + 1].m_uEndVertex, uCurV};

		pVB->unlock();
	}

	GXVERTEXELEMENT vertexDecl[] =
	{
		{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION, GXDECLSPEC_PER_VERTEX_DATA},
		GXDECL_END()
	};

	IGXVertexDeclaration *pVD = m_pDevice->createVertexDeclaration(vertexDecl);

	m_pRenderBuffer = m_pDevice->createRenderBuffer(1, &pVB, pVD);
	mem_release(pVB);
	mem_release(pVD);

	m_idVS = SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_grid.vs", "terrax_grid.vs", SHADER_CHECKDOUBLE_PATH);
	m_idPS = SGCore_ShaderLoad(SHADER_TYPE_PIXEL, "terrax_colored.ps", "terrax_colored.ps", SHADER_CHECKDOUBLE_PATH);
	m_idShaderKit = SGCore_ShaderCreateKit(m_idVS, m_idPS);

	GXBLEND_DESC blendDesc;
	blendDesc.renderTarget[0].bBlendEnable = TRUE;
	blendDesc.renderTarget[0].srcBlend = blendDesc.renderTarget[0].srcBlendAlpha = GXBLEND_SRC_ALPHA;
	blendDesc.renderTarget[0].destBlend = blendDesc.renderTarget[0].destBlendAlpha = GXBLEND_INV_SRC_ALPHA;

	m_pBlendState = m_pDevice->createBlendState(&blendDesc);

	blendDesc.renderTarget[0].bBlendEnable = FALSE;
	blendDesc.renderTarget[0].u8RenderTargetWriteMask = 0;
	m_pBlendStateNoColor = m_pDevice->createBlendState(&blendDesc);

	GXDEPTH_STENCIL_DESC dsDesc;
	dsDesc.bDepthEnable = FALSE;
	dsDesc.bStencilEnable = TRUE;
	dsDesc.stencilPassOp = GXSTENCIL_OP_INCR;
	m_pStencilPass0 = m_pDevice->createDepthStencilState(&dsDesc);

	dsDesc.stencilFunc = GXCOMPARISON_EQUAL;
	dsDesc.stencilPassOp = GXSTENCIL_OP_KEEP;
	m_pStencilPass1 = m_pDevice->createDepthStencilState(&dsDesc);
}

CGrid::~CGrid()
{
	mem_release(m_pBlendState);
	mem_release(m_pBlendStateNoColor);
	mem_release(m_pStencilPass0);
	mem_release(m_pStencilPass1);
	mem_release(m_pRenderBuffer);
}

void CGrid::render(GRID_STEP step)
{
	IGXBlendState *pOldBlendState = m_pDevice->getBlendState();
	IGXDepthStencilState *pOldDepthStencilState = m_pDevice->getDepthStencilState();
	SGCore_ShaderBind(m_idShaderKit);
	m_pDevice->setRenderBuffer(m_pRenderBuffer);
	SMMATRIX mViewProj, mWorld;
	Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &mViewProj);
	Core_RMatrixGet(G_RI_MATRIX_WORLD, &mWorld);
	SGCore_ShaderSetVRF(SHADER_TYPE_VERTEX, m_idVS, "g_mWVP", &SMMatrixTranspose(mWorld * mViewProj), 4);
	m_pDevice->setPrimitiveTopology(GXPT_LINELIST);

	GRID_STEP hiliteFrom = GRID_STEP_100M;
	switch(step)
	{
	case GRID_STEP_1CM:
		hiliteFrom = GRID_STEP_5CM;
		break;
	case GRID_STEP_2CM:
		hiliteFrom = GRID_STEP_10CM;
		break;
	case GRID_STEP_5CM:
	case GRID_STEP_10CM:
		hiliteFrom = GRID_STEP_50CM;
		break;
	case GRID_STEP_20CM:
		hiliteFrom = GRID_STEP_1M;
		break;
	case GRID_STEP_50CM:
	case GRID_STEP_1M:
		hiliteFrom = GRID_STEP_5M;
		break;
	case GRID_STEP_2M:
		hiliteFrom = GRID_STEP_10M;
		break;
	case GRID_STEP_5M:
	case GRID_STEP_10M:
		hiliteFrom = GRID_STEP_50M;
		break;
	case GRID_STEP_20M:
	case GRID_STEP_50M:
	case GRID_STEP_100M:
		hiliteFrom = GRID_STEP_100M;
		break;
	}
	if(m_isDotted)
	{
		m_pDevice->setBlendState(m_pBlendStateNoColor);
		m_pDevice->setDepthStencilState(m_pStencilPass0);

		for(GRID_STEP i = step; i <= GRID_STEP_MAXIMAL; i = (GRID_STEP)(i + 1))
		{
			if((step == GRID_STEP_2CM && i == GRID_STEP_5CM)
				|| (step == GRID_STEP_20CM && i == GRID_STEP_50CM)
				|| (step == GRID_STEP_2M && i == GRID_STEP_5M)
				|| (step == GRID_STEP_20M && i == GRID_STEP_50M)
				)
			{
				continue;
			}
			if(i == GRID_STEP_AXES)
			{
				m_pDevice->drawPrimitive(m_uVertexPerStep[i].m_uStartVertex, (m_uVertexPerStep[i].m_uEndVertex - m_uVertexPerStep[i].m_uStartVertex) / 2);
			}
			m_pDevice->drawPrimitive(m_uVertexPerStep[i].m_uStartVertex, (m_uVertexPerStep[i].m_uEndVertex - m_uVertexPerStep[i].m_uStartVertex) / 2);
		}

		m_pDevice->setDepthStencilState(m_pStencilPass1);
		m_pDevice->setStencilRef(2);
	}

	m_pDevice->setBlendState(m_pBlendState);
	for(GRID_STEP i = step; i <= GRID_STEP_MAXIMAL; i = (GRID_STEP)(i + 1))
	{
		float4 vColor = GRID_COLOR_REGULAR;
		if(i == GRID_STEP_10M || i == GRID_STEP_20M || i == GRID_STEP_50M)
		{
			vColor = GRID_COLOR_REGULAR_10M;
		}

		if((step == GRID_STEP_2CM && i == GRID_STEP_5CM)
			|| (step == GRID_STEP_20CM && i == GRID_STEP_50CM)
			|| (step == GRID_STEP_2M && i == GRID_STEP_5M)
			|| (step == GRID_STEP_20M && i == GRID_STEP_50M)
			)
		{
			continue;
		}

		if(i == GRID_STEP_AXES)
		{
			vColor = GRID_COLOR_AXES;
		}
		else if(i >= hiliteFrom)
		{
			if(i == GRID_STEP_10M || i == GRID_STEP_20M || i == GRID_STEP_50M)
			{
				vColor = GRID_COLOR_MAIN_10M;
			}
			else
			{
				vColor = GRID_COLOR_MAIN;
			}
		}

		

		vColor.w = m_fOpacity;
		SGCore_ShaderSetVRF(SHADER_TYPE_PIXEL, m_idPS, "g_vColor", &vColor, 1);
		m_pDevice->drawPrimitive(m_uVertexPerStep[i].m_uStartVertex, (m_uVertexPerStep[i].m_uEndVertex - m_uVertexPerStep[i].m_uStartVertex) / 2);
	}
	m_pDevice->setBlendState(pOldBlendState);
	if(m_isDotted)
	{
		m_pDevice->setDepthStencilState(pOldDepthStencilState);
	}

	SGCore_ShaderUnBind();

	mem_release(pOldBlendState);
	mem_release(pOldDepthStencilState);
}

GRID_STEP CGrid::GetMinStepForScale(float fScale)
{
	// at least 4 pixels between lines
	float f4pxStep = 4 * fScale;
	GRID_STEP out = GRID_STEP_100M;
	if(f4pxStep < 0.01f)
	{
		out = GRID_STEP_1CM;
	}
	else if(f4pxStep < 0.02f)
	{
		out = GRID_STEP_2CM;
	}
	else if(f4pxStep < 0.05f)
	{
		out = GRID_STEP_5CM;
	}
	else if(f4pxStep < 0.1f)
	{
		out = GRID_STEP_10CM;
	}
	else if(f4pxStep < 0.2f)
	{
		out = GRID_STEP_20CM;
	}
	else if(f4pxStep < 0.5f)
	{
		out = GRID_STEP_50CM;
	}
	else if(f4pxStep < 1.0f)
	{
		out = GRID_STEP_1M;
	}
	else if(f4pxStep < 2.0f)
	{
		out = GRID_STEP_2M;
	}
	else if(f4pxStep < 5.0f)
	{
		out = GRID_STEP_5M;
	}
	else if(f4pxStep < 10.0f)
	{
		out = GRID_STEP_10M;
	}
	else if(f4pxStep < 20.0f)
	{
		out = GRID_STEP_20M;
	}
	else if(f4pxStep < 50.0f)
	{
		out = GRID_STEP_50M;
	}

	return(out);
}

void CGrid::setOpacity(float fOpacity)
{
	m_fOpacity = fOpacity;
}

void CGrid::setDottedMode(bool isDotted)
{
	m_isDotted = isDotted;
}