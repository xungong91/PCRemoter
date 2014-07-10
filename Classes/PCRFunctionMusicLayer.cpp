#include "PCRFunctionMusicLayer.h"
bool PCRFunctionMusicLayer::init()
{
	if (!PCRFunctionBaseLayer::init())
	{
		return false;
	}
	m_uilayer = UILayer::create();
	UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI/RemoterUI_Music.json"));
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
	Slider_audio->addTouchEventListener(this,toucheventselector(PCRFunctionMusicLayer::Slider_audio_Event));

	ADD_WIDGRT_EVENT(Button_close,PCRFunctionMusicLayer)
	ADD_WIDGRT_EVENT(TextButton__Open,PCRFunctionMusicLayer)
	ADD_WIDGRT_EVENT(TextButton__Mini,PCRFunctionMusicLayer)
	ADD_WIDGRT_EVENT(TextButton__Lyrics,PCRFunctionMusicLayer)
	ADD_WIDGRT_EVENT(TextButton__Play,PCRFunctionMusicLayer) 
	ADD_WIDGRT_EVENT(TextButton__NotAudio,PCRFunctionMusicLayer)
	ADD_WIDGRT_EVENT(TextButton__AudioDown,PCRFunctionMusicLayer)
	ADD_WIDGRT_EVENT(TextButton__AudioUp,PCRFunctionMusicLayer)
	return true;
}

void PCRFunctionMusicLayer::Slider_audio_Event( CCObject* Obj,TouchEventType type )
{
	UISlider* slider=(UISlider*)Obj;
	if(type==TOUCH_EVENT_ENDED)
	{
		if (slider->getPercent()>50)
		{
			SendTcpMsg(FUNCTION_MUSIC_NEXTSONG,NULL,0);
		}
		else
		{
			SendTcpMsg(FUNCTION_MUSIC_ONSONG,NULL,0);
		}
		slider->setPercent(50);
	}
}

void PCRFunctionMusicLayer::TextButton__Open_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_OPEN,NULL,0);
	}
}

void PCRFunctionMusicLayer::TextButton__Mini_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_MINI,NULL,0);
	}
}

void PCRFunctionMusicLayer::TextButton__Lyrics_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_LYC,NULL,0);
	}
}

void PCRFunctionMusicLayer::TextButton__Play_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_PLAY,NULL,0);
	}
}

void PCRFunctionMusicLayer::TextButton__NotAudio_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_NOTAUDIO,NULL,0);
	}
}

void PCRFunctionMusicLayer::TextButton__AudioDown_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_DOWNAUDIO,NULL,0);
	}
}

void PCRFunctionMusicLayer::TextButton__AudioUp_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendTcpMsg(FUNCTION_MUSIC_UPAUDIO,NULL,0);
	}
}

