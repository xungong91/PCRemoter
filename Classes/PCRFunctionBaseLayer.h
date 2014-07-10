#ifndef _PCR_FUNCTION_BASE_LAYER_H
#define _PCR_FUNCTION_BASE_LAYER_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class PCRFunctionDelegate
{
public:
	virtual void OnCloseLayer(CCLayer* layer){};
};
class PCRFunctionBaseLayer:public CCLayer
{
#define ADD_WIDGRT_EVENT(WID_NAME,WIDTYPE) \
	UIWidget* WID_NAME= UIHelper::seekWidgetByName(UI_Dialog, #WID_NAME); \
	WID_NAME->addTouchEventListener(this,toucheventselector(WIDTYPE::WID_NAME ## _Event));
public:
	bool init();
	PCRFunctionBaseLayer();
	~PCRFunctionBaseLayer();
	UILayer *m_uilayer;
	Layout *UI_Dialog;
	void SetDelegate(PCRFunctionDelegate *_delegate);
	void Button_close_Event(CCObject* Obj,TouchEventType type);
	static void SendMsg(int type,char* data,int len);
	static void SendTcpMsg(int type,char* data,int len);
protected:
	PCRFunctionDelegate* m_delegate;
};

#endif

