#include "PCRFunctionSystemLayer.h"
bool PCRFunctionSystemLayer::init()
{
	if (!PCRFunctionBaseLayer::init())
	{
		return false;
	}
	m_uilayer = UILayer::create();
	UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI/RemoterUI_System.json"));
	m_uilayer->addWidget(UI_Dialog);
	this->addChild(m_uilayer,1);

	UISlider* Slider_audio = UISlider::create();
	Slider_audio->setTouchEnabled(true);
	Slider_audio->setZOrder(1);
	Slider_audio->loadBarTexture("RemoterUI/list_2001@2x.png");
	Slider_audio->loadSlidBallTextures("RemoterUI/slienl1.png", "RemoterUI/slienl2.png", "");
	//Slider_audio->loadProgressBarTexture("cocosgui/sliderProgress.png");
	Slider_audio->setScaleX(0.8);
	Slider_audio->setPercent(50);
	Slider_audio->setScaleY(0.7);
	Slider_audio->setPosition(ccp(164, 137));
	m_uilayer->addWidget(Slider_audio);
	Slider_audio->addTouchEventListener(this,toucheventselector(PCRFunctionSystemLayer::Slider_audio_Event));
	
	ADD_WIDGRT_EVENT(Button_close,PCRFunctionSystemLayer)
	//ADD_WIDGRT_EVENT(Slider_audio,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(TextButton_down,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(TextButton__escdown,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(TextButton__restart,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(TextButton__sleep,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(Button_audio_up,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(Button_audio_down,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(Button_audio_pause,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(TextButton__Esc,PCRFunctionSystemLayer)
	ADD_WIDGRT_EVENT(TextButton__Schalt,PCRFunctionSystemLayer)
	return true;
}
void PCRFunctionSystemLayer::Slider_audio_Event( CCObject* Obj,TouchEventType type )
{
	UISlider* slider=(UISlider*)Obj;
	if(type==TOUCH_EVENT_ENDED)
	{
		if (slider->getPercent()>50)
		{
			SendTcpMsg(FUNCTION_AUDIO_DOWN,NULL,0);
		}
		else
		{
			SendTcpMsg(FUNCTION_AUDIO_UP,NULL,0);
		}
		slider->setPercent(50);
	}
}
void PCRFunctionSystemLayer::TextButton_down_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_SHUTDOWN,NULL,0);
	}
}

void PCRFunctionSystemLayer::TextButton__escdown_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_CANCELSHUTDOWN,NULL,0);
	}
}

void PCRFunctionSystemLayer::TextButton__restart_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_RESTART,NULL,0);
	}
}

void PCRFunctionSystemLayer::TextButton__sleep_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_DORMANCY,NULL,0);
	}
}

void PCRFunctionSystemLayer::Button_audio_up_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_AUDIO_UP,NULL,0);
	}
}

void PCRFunctionSystemLayer::Button_audio_down_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_AUDIO_DOWN,NULL,0);
	}
}

void PCRFunctionSystemLayer::Button_audio_pause_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_AUDIO_MUTE,NULL,0);
	}
}

void PCRFunctionSystemLayer::TextButton__Schalt_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_SCHALT,NULL,0);
	}
}

void PCRFunctionSystemLayer::TextButton__Esc_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_ESC,NULL,0);
	}
}
