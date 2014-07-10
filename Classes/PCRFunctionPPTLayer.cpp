#include "PCRFunctionPPTLayer.h"
bool PCRFunctionPPTLayer::init()
{
	if (!PCRFunctionBaseLayer::init())
	{
		return false;
	}
	m_uilayer = UILayer::create();
	UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI/RemoterUI_PPT.json"));
	m_uilayer->addWidget(UI_Dialog);
	this->addChild(m_uilayer,1);

	ADD_WIDGRT_EVENT(Button_close,PCRFunctionPPTLayer)
	ADD_WIDGRT_EVENT(TB_QuitScreen,PCRFunctionPPTLayer)
	ADD_WIDGRT_EVENT(TB_FullScreen,PCRFunctionPPTLayer)
	ADD_WIDGRT_EVENT(TB_Up,PCRFunctionPPTLayer)
	ADD_WIDGRT_EVENT(TB_Down,PCRFunctionPPTLayer)

	UICheckBox* CheckBox_Gravity=(UICheckBox*)m_uilayer->getWidgetByName("CheckBox_Gravity");
	CheckBox_Gravity->addEventListenerCheckBox(this, checkboxselectedeventselector(PCRFunctionPPTLayer::EditSelectd));

	return true;
}
void PCRFunctionPPTLayer::didAccelerate( cocos2d::CCAcceleration* pAccelerationValue )
{
	float m_x=pAccelerationValue->x;
	float m_y=pAccelerationValue->y;
	float m_z=pAccelerationValue->z;
	float m_s=pAccelerationValue->timestamp;
	//手机正面朝上;
	if(m_z<-0.9&&CURTIME>m_curtime)
	{
		if(m_x>0.8)
		{
			lablex->setString("right");
			SendMsg(FUNCTION_PPT_UP,NULL,0);
			m_curtime=CURTIME+1000;
		}
		else if(m_x<-0.8)
		{
			lablex->setString("left");
			SendMsg(FUNCTION_PPT_DOWN,NULL,0);
			m_curtime=CURTIME+1000;
		}
	}
	char charchar[100];
	sprintf(charchar,"x: %f\ny: %f\nz: %f\ns: %f",m_x,m_y,m_z,m_s);
	lablettf->setString(charchar);
	//CCMessageBox(charchar,"Title");
	return;

	//控制减速的速率值越小，更容易改变方向   
	float deceleration = 0.5f;   
	//加速计的敏感值越大，主角对加速计的输入会越敏感   
	float sensitivity = 10.0;   
	//最大移动距离   
	float maxVelocity = 100.0f;   

	float m_myCarMoveDis=1;
	m_myCarMoveDis = m_myCarMoveDis*deceleration + pAccelerationValue->x*sensitivity;   
	if (m_myCarMoveDis>=maxVelocity)   
	{   
		m_myCarMoveDis = maxVelocity;   
	} 
	else if(m_myCarMoveDis <=-maxVelocity)   
	{   
		m_myCarMoveDis = -maxVelocity;   
	}  
}
void PCRFunctionPPTLayer::EditSelectd( CCObject* obj , CheckBoxEventType type)
{
	//重力感应
	if (type == CHECKBOX_STATE_EVENT_SELECTED)
	{
		CCSize _phsiz=CCDirector::sharedDirector()->getWinSize();
		lablettf=CCLabelTTF::create("string", "Marker Felt", 22);
		lablex=CCLabelTTF::create("center", "Marker Felt", 22);
		lablex->setColor(ccBLACK);
		lablettf->setColor(ccBLACK);
		lablettf->setPosition(ccp(_phsiz.width*1/2,_phsiz.height/5));
		lablex->setPosition(ccp(_phsiz.width*1/2,_phsiz.height/8));
		this->addChild(lablettf,2);
		this->addChild(lablex,2);
		this->setAccelerometerEnabled(true);
	}
	else if(type == CHECKBOX_STATE_EVENT_UNSELECTED)
	{
		this->setAccelerometerEnabled(false);
		this->removeChild(lablettf);
		this->removeChild(lablex);
	}
}

void PCRFunctionPPTLayer::TB_QuitScreen_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendMsg(FUNCTION_PPT_QUITSCREEN,NULL,0);
	}
}

void PCRFunctionPPTLayer::TB_FullScreen_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendMsg(FUNCTION_PPT_FULLSCREEN,NULL,0);
	}
}

void PCRFunctionPPTLayer::TB_Up_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendMsg(FUNCTION_PPT_UP,NULL,0);
	}
}

void PCRFunctionPPTLayer::TB_Down_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendMsg(FUNCTION_PPT_DOWN,NULL,0);
	}
}

