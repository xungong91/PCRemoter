#ifndef _PCR_MAIN_SCENE_H_
#define _PCR_MAIN_SCENE_H_

#include "cocos2d.h"
#include "PCRLoginLayer.h"
#include "PCRMapLayer.h"
#include "ControlLayer.h"
USING_NS_CC;

class PCRMainScene:public CCScene
{
public:
	static PCRMainScene* Singleton();
	~PCRMainScene();
	virtual void onEnter();
	virtual void onExit();
	void GotoLoginLayer();
	void GotoMapLayer();
	void GotoControlLayer();
	char* m_ip;
	int m_port;
protected:
	static PCRMainScene* m_PCRMainScene;
	CREATE_FUNC(PCRMainScene);
	bool init();
	PCRMainScene();
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (PCRMainScene::m_PCRMainScene)
			{
				delete PCRMainScene::m_PCRMainScene;
			}
		}
	};
	static CGarbo cgarbo;
	PCRLoginLayer* loginlayer;
	PCRMapLayer* maplayer;
	ControlLayer* mControlLayer;
	void NotificationCB(float dt);
	void SeverSendMsgCB(CCObject* obj);
};
#endif

