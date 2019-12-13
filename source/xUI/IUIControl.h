#ifndef __IUICONTROL_H
#define __IUICONTROL_H

#include <gdefines.h>

class IUIControl : public IXUnknown
{
	//! Метод установки контента в контроле
	virtual void XMETHODCALLTYPE setLabel(const char *szTitle) = 0;

	//! Метод установки позиции в окне
	virtual void XMETHODCALLTYPE setPosition(int iPosX, int iPosY) = 0;

	//! Метод установки видимости для контрола
	virtual void XMETHODCALLTYPE setVisible(bool bVisible) = 0;

	//! Метод установки размера по высоте и ширине
	virtual void XMETHODCALLTYPE setSize(int iSizeX, int iSizeY) = 0;

	//! Метод возвращает видимость контрола
	virtual bool XMETHODCALLTYPE isVisible() = 0;

	//! Метод устанавливает имя элемента
	virtual bool XMETHODCALLTYPE setName(const char *szName) = 0;
};

#endif