#ifndef _PCR_MAP_LAYER_H_
#define _PCR_MAP_LAYER_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PCRFunctionBaseLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
class PCRMapLayer:public CCLayer,public PCRFunctionDelegate
{
public:
	CREATE_FUNC(PCRMapLayer);
	bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void OnCloseLayer(CCLayer* layer);
protected:
	UILayer *m_uilayer;
	void TextButton_Close_Event(CCObject* Obj,TouchEventType type);
	void Button_System_Event(CCObject* Obj,TouchEventType type);
	void Button_Handle_Event(CCObject* Obj,TouchEventType type);
	void Button_PPT_Event(CCObject* Obj,TouchEventType type);
	void Button_Camera_Event(CCObject* Obj,TouchEventType type);
	void Button_Music_Event(CCObject* Obj,TouchEventType type);
};
#endif

