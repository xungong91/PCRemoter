#ifndef _PCR_LOGIN_LAYER_H_
#define _PCR_LOGIN_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class PCRLoginLayer:public CCLayer
{
public:
	CREATE_FUNC(PCRLoginLayer);
	bool init();
	UILayer *m_uilayer;
	virtual void onEnter();
	virtual void onExit();
	void TextButton_Enter_Event(CCObject* Obj,TouchEventType type);
	void Button_Close_Event(CCObject* Obj,TouchEventType type);
	UITextField *TextField_Key,*TextField_IP;
protected:
};
#endif