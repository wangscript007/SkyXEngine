#ifndef _IVIDEO_H_
#define _IVIDEO_H_

#include "DOM.h"
#include "VideoRenderer.h"

namespace gui
{
	namespace dom
	{
		class IVIDEO: public IDOMnodeTag
		{
		public:
			DECLARE_CLASS(IVIDEO, IDOMnodeTag);
			DECLARE_DOM_NODE(IVIDEO);

			StringW initRenderer()
			{
				StringW vid = StringW(L"!video#") + StringW((int)m_renderer.getInstanceId());
				if(!m_renderer.isLoaded())
				{
					StringW src = getAttribute(L"src");
					StringW path = StringW(GetGUI()->getResourceDir()) + L"/video/" + src;
					m_renderer.openFile(path.c_str());

					CTextureManager::addTexture(vid, m_renderer.getTexture());
					if(getAttribute(L"autoplay").toBool())
					{
						m_renderer.play();
					}
					m_renderer.setLooped(getAttribute(L"looped").toBool());
				}
				return(vid);
			}

			CVideoRenderer * GetVideoRenderer()
			{
				return(&m_renderer);
			}

		protected:

			CVideoRenderer m_renderer;
		};
	};
};

#endif
