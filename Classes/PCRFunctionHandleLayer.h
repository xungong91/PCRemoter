#ifndef _PCR_FUNCTION_HANDLE_LAYER_H_
#define _PCR_FUNCTION_HANDLE_LAYER_H_

#include "PCRFunctionBaseLayer.h"
#include "CCJoyStick.h"
#include "GFileHelper.h"
#include <string>
using namespace std;

////class MyJoyStickDelegate : public CCJoyStickDelegate
////{
////public:
////	void onCCJoyStickUpdate(cocos2d::CCNode* sender,float angle,cocos2d::CCPoint direction,float power);
////	void onCCJoyStickActivated(cocos2d::CCNode* sender);
////	void onCCJoyStickDeactivated(cocos2d::CCNode* sender);
////	KeyboardShortcuts m_keyboar;
////	char selectchar;
////	~MyJoyStickDelegate();
////protected:
////};

class PCRFunctionHandleLayer:public PCRFunctionBaseLayer,public CCJoyStickDelegate
{
public:
	CREATE_FUNC(PCRFunctionHandleLayer);
	~PCRFunctionHandleLayer();
	bool init();
	void GetTfStringValue();
	void SetTfStringValue();
	void SetTouchBOOL(UIWidget* widget,bool b);
	void EditSelectd(CCObject* obj , CheckBoxEventType type);
	virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

	void Button_a_Event(CCObject* Obj,TouchEventType type);
	void Button_b_Event(CCObject* Obj,TouchEventType type);
	void Button_c_Event(CCObject* Obj,TouchEventType type);
	void Button_d_Event(CCObject* Obj,TouchEventType type);
	void Button_e_Event(CCObject* Obj,TouchEventType type);
	void Button_f_Event(CCObject* Obj,TouchEventType type);

	void onCCJoyStickUpdate(cocos2d::CCNode* sender,float angle,cocos2d::CCPoint direction,float power);
	void onCCJoyStickActivated(cocos2d::CCNode* sender);
	void onCCJoyStickDeactivated(cocos2d::CCNode* sender);
	char selectchar;  //·½ÏòµÄ
private:
	CCJoystick* createJoystick();
	CCJoystick* joyStick;
	UIWidget *ImageView_bg,*Panel_input,*Panel;
	KeyboardShortcuts m_keyboar;
	char selectGravity;
};

#endif

