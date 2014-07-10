#ifndef _PCR_FUNCTION_PPT_LAYER_H_
#define _PCR_FUNCTION_PPT_LAYER_H_
#include "PCRFunctionBaseLayer.h"
class PCRFunctionPPTLayer:public PCRFunctionBaseLayer
{
public:
	CREATE_FUNC(PCRFunctionPPTLayer);
	bool init();
	void TB_QuitScreen_Event(CCObject* Obj,TouchEventType type);
	void TB_FullScreen_Event(CCObject* Obj,TouchEventType type);
	void TB_Up_Event(CCObject* Obj,TouchEventType type);
	void TB_Down_Event(CCObject* Obj,TouchEventType type);
	//重力感应
	virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
	cocos2d::CCLabelTTF* lablettf;
	cocos2d::CCLabelTTF* lablex;
	float m_curtime;
	void EditSelectd(CCObject* obj, CheckBoxEventType type);
private:

};
#endif