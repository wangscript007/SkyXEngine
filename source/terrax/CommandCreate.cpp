#include "CommandCreate.h"
#include <common/aastring.h>

extern AssotiativeArray<AAString, IXEditable*> g_mEditableSystems;

CCommandCreate::CCommandCreate(const float3_t vPos, const char *szTypeName, const char *szClassName)
{
	m_vPos = vPos;
	m_sClassName = szClassName;

	const AssotiativeArray<AAString, IXEditable*>::Node *pNode;
	if(!g_mEditableSystems.KeyExists(AAString(szTypeName), &pNode))
	{
		assert(!"Invalid type name!");
		return;
	}

	m_pEditable = *(pNode->Val);
}

CCommandCreate::~CCommandCreate()
{
	mem_release(m_pObject);
}

bool CCommandCreate::exec()
{
	if(!m_pObject)
	{
		m_pObject = m_pEditable->newObject(m_sClassName.c_str());
	}
	m_pObject->setPos(m_vPos);
	m_pObject->setSelected(true);
	m_pObject->create();

	g_pLevelObjects.push_back(m_pObject);
	return(true);
}
bool CCommandCreate::undo()
{
	m_pObject->remove();
	g_pLevelObjects.erase(g_pLevelObjects.size() - 1);

	return(true);
}