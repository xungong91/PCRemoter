#include "PCRFunctionHandleLayer.h"
#include "PCRClient.h"
#include "PCRMsgSendQueue.h"
bool PCRFunctionHandleLayer::init()
{
	if (!PCRFunctionBaseLayer::init())
	{
		return false;
	}
	m_keyboar.Get();
	m_uilayer = UILayer::create();
	this->addChild(m_uilayer,0);
	joyStick=createJoystick();
	this->addChild(joyStick,0);

	UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI/RemoterUI_Handle.json"));
	m_uilayer->addWidget(UI_Dialog);

	ImageView_bg=(UIWidget*)m_uilayer->getWidgetByName("ImageView_bg");
	Panel_input=(UIWidget*)m_uilayer->getWidgetByName("Panel_input");
	Panel=(UIWidget*)m_uilayer->getWidgetByName("Panel");
	UICheckBox* CheckBox_Start=(UICheckBox*)m_uilayer->getWidgetByName("CheckBox_Start");
	CheckBox_Start->addEventListenerCheckBox(this,checkboxselectedeventselector(PCRFunctionHandleLayer::EditSelectd));

	UICheckBox* CheckBox_Gravity=(UICheckBox*)m_uilayer->getWidgetByName("CheckBox_Gravity");
	CheckBox_Gravity->addEventListenerCheckBox(this,checkboxselectedeventselector(PCRFunctionHandleLayer::EditSelectd));

		ADD_WIDGRT_EVENT(Button_close,PCRFunctionHandleLayer)
		ADD_WIDGRT_EVENT(Button_a,PCRFunctionHandleLayer)
		ADD_WIDGRT_EVENT(Button_b,PCRFunctionHandleLayer)
		ADD_WIDGRT_EVENT(Button_c,PCRFunctionHandleLayer)
		ADD_WIDGRT_EVENT(Button_d,PCRFunctionHandleLayer)
		ADD_WIDGRT_EVENT(Button_e,PCRFunctionHandleLayer)
		ADD_WIDGRT_EVENT(Button_f,PCRFunctionHandleLayer)
	SetTouchBOOL(Panel_input,false);
	return true;
}
PCRFunctionHandleLayer::~PCRFunctionHandleLayer()
{
	m_keyboar.Save();
}
void PCRFunctionHandleLayer::didAccelerate( cocos2d::CCAcceleration* pAccelerationValue )
{
	float m_x=pAccelerationValue->x;
	float m_y=pAccelerationValue->y;
	float m_z=pAccelerationValue->z;
	float m_s=pAccelerationValue->timestamp;
	if (m_z>0||m_x>0.05||m_x<-0.05)
	{
		return;
	}
	else if (m_z>-0.9f&&m_y<0)
	{
		if (selectGravity!=ARROWKEYSRIGHT)
		{
			char dataup[]={selectGravity};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			char datadown[]={ARROWKEYSRIGHT};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_DOWN,datadown,1);
			selectGravity=ARROWKEYSRIGHT;
		}
	}
	else if (m_z>-0.9f&&m_y>0)
	{
		if (selectGravity!=ARROWKEYSLEFT)
		{
			char dataup[]={selectGravity};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			char datadown[]={ARROWKEYSLEFT};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_DOWN,datadown,1);
			selectGravity=ARROWKEYSLEFT;
		}
	}
	else if (m_z<-0.9)
	{
		if (selectGravity!=0x0)
		{
			char dataup[]={selectGravity};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			selectGravity=0x0;
		}
	}
}
void PCRFunctionHandleLayer::EditSelectd( CCObject* obj, CheckBoxEventType type )
{
	if (type == CHECKBOX_STATE_EVENT_SELECTED)
	{
		UIWidget *widget=(UIWidget*)obj;
		if (strcmp(widget->getName(),"CheckBox_Start"))
		{
			SetTouchBOOL(Panel_input,true);
			SetTouchBOOL(ImageView_bg,false);
			GetTfStringValue();
			joyStick->setVisible(false);
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(joyStick);
		}
		else
		{
			this->setAccelerometerEnabled(true);
		}
	}
	else if (type = CHECKBOX_STATE_EVENT_UNSELECTED)
	{
		UIWidget *widget=(UIWidget*)obj;
		if (strcmp(widget->getName(),"CheckBox_Start"))
		{
			SetTouchBOOL(Panel_input,false);
			SetTouchBOOL(ImageView_bg,true);
			SetTfStringValue();
			joyStick->setVisible(true);
			CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(joyStick, 0, true);
		}
		else
		{
			this->setAccelerometerEnabled(false);
		}
	}
}

void PCRFunctionHandleLayer::GetTfStringValue()
{
#define GET_TFTEXT(TF_NAME) \
	UITextField *TF_NAME=(UITextField*)m_uilayer->getWidgetByName(#TF_NAME); \
	TF_NAME->setText(m_keyboar.TF_NAME.c_str())
	GET_TFTEXT(TF_a);
	GET_TFTEXT(TF_b);
	GET_TFTEXT(TF_c);
	GET_TFTEXT(TF_d);
	GET_TFTEXT(TF_e);
	GET_TFTEXT(TF_f);
	GET_TFTEXT(TF_up);
	GET_TFTEXT(TF_down);
	GET_TFTEXT(TF_right);
	GET_TFTEXT(TF_left);
}

void PCRFunctionHandleLayer::SetTfStringValue()
{
#define SET_TFTEXT(TF_NAME) \
	UITextField *TF_NAME=(UITextField*)m_uilayer->getWidgetByName(#TF_NAME); \
	m_keyboar.TF_NAME =TF_NAME->getStringValue();
	SET_TFTEXT(TF_a);
	SET_TFTEXT(TF_b);
	SET_TFTEXT(TF_c);
	SET_TFTEXT(TF_d);
	SET_TFTEXT(TF_e);
	SET_TFTEXT(TF_f);
	SET_TFTEXT(TF_up);
	SET_TFTEXT(TF_down);
	SET_TFTEXT(TF_right);
	SET_TFTEXT(TF_left);
}

void PCRFunctionHandleLayer::SetTouchBOOL( UIWidget* widget,bool b )
{
	if (widget==Panel_input)
	{
		widget->setVisible(b);
	}
	CCArray *ccarray=widget->getChildren();
	CCObject *obj;
	CCARRAY_FOREACH(ccarray,obj)
	{
		UIWidget* item=(UIWidget*)obj;
		item->setTouchEnabled(b);
	}
}



CCJoystick* PCRFunctionHandleLayer::createJoystick()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCJoystick* joyStick = CCJoystick::create(20, 50, false, true, false, false);
	joyStick->setPosition(ccp(0.3 * size.width,0.8 * size.height));
	joyStick->setBallTexture("buttonpress.png");
	joyStick->setStickTexture("stick.png");
	joyStick->setDockTexture("joystickbg.png");
	joyStick->setDelegate(this);
	joyStick->setTouchEnabled(true);
	return joyStick;
}

void PCRFunctionHandleLayer::Button_a_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=(char*)m_keyboar.TF_a.c_str();
		SendMsg(FUNCTION_KEY_DOWN,data,1);
	}
	else if(type==TOUCH_EVENT_ENDED)
	{
	char* data=(char*)m_keyboar.TF_a.c_str();
	SendMsg(FUNCTION_KEY_UP,data,1);
	}
}

void PCRFunctionHandleLayer::Button_b_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=(char*)m_keyboar.TF_b.c_str();
		SendMsg(FUNCTION_KEY_DOWN,data,1);
	}
	else if(type==TOUCH_EVENT_ENDED)
	{
	char* data=(char*)m_keyboar.TF_b.c_str();
	SendMsg(FUNCTION_KEY_UP,data,1);
	}
}

void PCRFunctionHandleLayer::Button_c_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=(char*)m_keyboar.TF_c.c_str();
		SendMsg(FUNCTION_KEY_DOWN,data,1);
	}
	else if(type==TOUCH_EVENT_ENDED)
	{
	char* data=(char*)m_keyboar.TF_c.c_str();
	SendMsg(FUNCTION_KEY_UP,data,1);
	}
}

void PCRFunctionHandleLayer::Button_d_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=(char*)m_keyboar.TF_d.c_str();
		SendMsg(FUNCTION_KEY_DOWN,data,1);
	}
	else if(type==TOUCH_EVENT_ENDED)
	{
	char* data=(char*)m_keyboar.TF_d.c_str();
	SendMsg(FUNCTION_KEY_UP,data,1);
	}
}

void PCRFunctionHandleLayer::Button_e_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=(char*)m_keyboar.TF_e.c_str();
		SendMsg(FUNCTION_KEY_DOWN,data,1);
	}
	else if(type==TOUCH_EVENT_ENDED)
	{
	char* data=(char*)m_keyboar.TF_e.c_str();
	SendMsg(FUNCTION_KEY_UP,data,1);
	}
}

void PCRFunctionHandleLayer::Button_f_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=(char*)m_keyboar.TF_f.c_str();
		SendMsg(FUNCTION_KEY_DOWN,data,1);
	}
	else if(type==TOUCH_EVENT_ENDED)
	{
	char* data=(char*)m_keyboar.TF_f.c_str();
	SendMsg(FUNCTION_KEY_UP,data,1);
	}
}

void PCRFunctionHandleLayer::onCCJoyStickUpdate( cocos2d::CCNode* sender,float angle,cocos2d::CCPoint direction,float power )
{
	if (angle>=-30&&angle<30)
	{
		if (selectchar!=ARROWKEYSUP)
		{
			char dataup[]={selectchar};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			char datadown[]={ARROWKEYSUP};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_DOWN,datadown,1);
			selectchar=ARROWKEYSUP;
		}
	}
	else if(angle>=30&&angle<60)
	{
		//TF_up
		//TF_left
	}
	else if(angle>=60&&angle<120)
	{
		if (selectchar!=ARROWKEYSLEFT)
		{
			char dataup[]={selectchar};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			char datadown[]={ARROWKEYSLEFT};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_DOWN,datadown,1);
			selectchar=ARROWKEYSLEFT;
		}
	}
	else if(angle>=120&&angle<150)
	{
		//TF_up
		//TF_left
	}
	else if(angle>=150||angle<-150)
	{
		if (selectchar!=ARROWKEYSDOWN)
		{
			char dataup[]={selectchar};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			char datadown[]={ARROWKEYSDOWN};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_DOWN,datadown,1);
			selectchar=ARROWKEYSDOWN;
		}
	}
	else if(angle>=-150&&angle<-120)
	{
		//TF_up
		//TF_left
	}
	else if(angle>=-120&&angle<-60)
	{
		if (selectchar!=ARROWKEYSRIGHT)
		{
			char dataup[]={selectchar};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
			char datadown[]={ARROWKEYSRIGHT};
			PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_DOWN,datadown,1);
			selectchar=ARROWKEYSRIGHT;
		}
	}
	else if(angle>=-60&&angle<-30)
	{
		//TF_up
		//TF_left
	}
}

void PCRFunctionHandleLayer::onCCJoyStickActivated( cocos2d::CCNode* sender )
{
	
}

void PCRFunctionHandleLayer::onCCJoyStickDeactivated( cocos2d::CCNode* sender )
{
	char dataup[]={selectchar};
	PCRFunctionBaseLayer::SendMsg(FUNCTION_KEY_UP,dataup,1);
	selectchar=0x0;
}
