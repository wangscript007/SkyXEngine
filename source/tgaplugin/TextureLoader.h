#ifndef __TEXTURELOADER_H
#define __TEXTURELOADER_H

#include <xcommon/IXTextureLoader.h>
#include <xcommon/IFileSystem.h>
#include "TGAFile.h"

class CTextureLoader: public IXUnknownImplementation<IXTextureLoader>
{
public:
	CTextureLoader(IFileSystem *pFileSystem);

	UINT XMETHODCALLTYPE getVersion() override;

	UINT XMETHODCALLTYPE getExtCount() const override;
	const char* XMETHODCALLTYPE getExt(UINT uIndex) const override;
	const char* XMETHODCALLTYPE getExtText(UINT uIndex) const override;
	const char* XMETHODCALLTYPE getAuthor() const override;
	const char* XMETHODCALLTYPE getCopyright() const override;
	const char* XMETHODCALLTYPE getDescription() const override;

	bool XMETHODCALLTYPE open(const char *szFileName, const char *szArg) override;
	GXTEXTURE_TYPE XMETHODCALLTYPE getType() const override;
	bool XMETHODCALLTYPE loadAs2D(IXResourceTexture2D *pResource) override;
	bool XMETHODCALLTYPE loadAsCube(IXResourceTextureCube *pResource) override;
	void XMETHODCALLTYPE getInfo(XTextureInfo *pTextureInfo) override;
	void XMETHODCALLTYPE close() override;

	GXFORMAT getFormat();

protected:

	bool loadUncompressedRGB(IXResourceTexture2D *pResource);
	
protected:
	IFileSystem *m_pFileSystem;

	IFile *m_pCurrentFile = NULL;
	TGA_Header m_tgaHeader;
	GXFORMAT m_format;
};

#endif
