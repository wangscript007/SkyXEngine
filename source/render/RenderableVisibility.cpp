#include "RenderableVisibility.h"

CRenderableVisibility::CRenderableVisibility(ID idPlugin, UINT uRenderSystems):
	m_uRenderSystems(uRenderSystems),
	m_idPlugin(idPlugin)
{
	m_ppVisibilities = new IXRenderableVisibility*[uRenderSystems];
	memset(m_ppVisibilities, 0, sizeof(IXRenderableVisibility*) * uRenderSystems);
}

CRenderableVisibility::~CRenderableVisibility()
{
	for(UINT i = 0; i < m_uRenderSystems; ++i)
	{
		mem_release(m_ppVisibilities[i]);
	}
	mem_delete_a(m_ppVisibilities);
}

ID CRenderableVisibility::getPluginId()
{
	return(m_idPlugin);
}

void CRenderableVisibility::setOcclusionCuller(IXOcclusionCuller *pOcclusionCuller)
{
	for(UINT i = 0; i < m_uRenderSystems; ++i)
	{
		if(m_ppVisibilities[i])
		{
			m_ppVisibilities[i]->setOcclusionCuller(pOcclusionCuller);
		}
	}
}

void CRenderableVisibility::updateForCamera(ICamera *pCamera, const IXRenderableVisibility *pReference)
{
	CRenderableVisibility *pRef = NULL;
	if(pReference)
	{
		assert(((IXRenderableVisibility*)pReference)->getPluginId() == getPluginId());
		pRef = (CRenderableVisibility*)pReference;
	}

	for(UINT i = 0; i < m_uRenderSystems; ++i)
	{
		if(m_ppVisibilities[i])
		{
			m_ppVisibilities[i]->updateForCamera(pCamera, pRef ? pRef->getVisibility(i) : NULL);
		}
	}
}

void CRenderableVisibility::updateForFrustum(IFrustum *pFrustum, const IXRenderableVisibility *pReference)
{
	CRenderableVisibility *pRef = NULL;
	if(pReference)
	{
		assert(((IXRenderableVisibility*)pReference)->getPluginId() == -1);
		pRef = (CRenderableVisibility*)pReference;
	}

	for(UINT i = 0; i < m_uRenderSystems; ++i)
	{
		if(m_ppVisibilities[i])
		{
			m_ppVisibilities[i]->updateForFrustum(pFrustum, pRef ? pRef->getVisibility(i) : NULL);
		}
	}
}

IXRenderableVisibility *CRenderableVisibility::getVisibility(ID id)
{
	assert(ID_VALID(id) && (UINT)id < m_uRenderSystems);

	return(m_ppVisibilities[id]);
}

void CRenderableVisibility::setVisibility(ID id, IXRenderableVisibility *pVisibility)
{
	assert(ID_VALID(id) && (UINT)id < m_uRenderSystems);

	mem_release(m_ppVisibilities[id]);

	m_ppVisibilities[id] = pVisibility;

	if(pVisibility)
	{
		pVisibility->AddRef();
	}
}