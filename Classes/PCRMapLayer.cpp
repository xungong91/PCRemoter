#include "PCRMapLayer.h"
#include "PCRMainScene.h"
#include "PCRClient.h"
#include "PCRFunctionSystemLayer.h"
#include "PCRFunctionHandleLayer.h"
#include "PCRFunctionPPTLayer.h"
#include "PCRFunctionMusicLayer.h"
#include "PCRFunctionCameraLayer.h"
bool PCRMapLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}

void PCRMapLayer::onEnter()
{
	CCLayer::onEnter();
	m_uilayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI_Main/RemoterUI_Main.ExportJson"));
	m_uilayer->addWidget(UI_Dialog);
	this->addChild(m_uilayer,1);

#define ADD_WIDGRT_EVENT(WID_NAME) \
	UIWidget* WID_NAME= UIHelper::seekWidgetByName(UI_Dialog, #WID_NAME); \
	WID_NAME->addTouchEventListener(this,toucheventselector(PCRMapLayer::WID_NAME ## _Event));

	ADD_WIDGRT_EVENT(TextButton_Close)
	ADD_WIDGRT_EVENT(Button_System)
	ADD_WIDGRT_EVENT(Button_Handle)
	ADD_WIDGRT_EVENT(Button_PPT)
	ADD_WIDGRT_EVENT(Button_Camera)
	ADD_WIDGRT_EVENT(Button_Music)

}

void PCRMapLayer::onExit()
{
	CCLayer::onExit();
}

void PCRMapLayer::TextButton_Close_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		PCRClient::Singleton()->m_client.Close();
		PCRMainScene::Singleton()->GotoLoginLayer();
	}
}

void PCRMapLayer::Button_System_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		PCRFunctionSystemLayer* layer=PCRFunctionSystemLayer::create();
		layer->SetDelegate(this);
		this->addChild(layer,2);
	}
}

void PCRMapLayer::Button_Handle_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		PCRFunctionHandleLayer* layer=PCRFunctionHandleLayer::create();
		layer->SetDelegate(this);
		this->addChild(layer,2);
	}
}
void PCRMapLayer::Button_PPT_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		PCRFunctionPPTLayer* layer=PCRFunctionPPTLayer::create();
		layer->SetDelegate(this);
		this->addChild(layer,2);
	}
}
void PCRMapLayer::Button_Camera_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		PCRFunctionCameraLayer* layer=PCRFunctionCameraLayer::create();
		layer->SetDelegate(this);
		this->addChild(layer,2);
	}
}
void PCRMapLayer::Button_Music_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		PCRFunctionMusicLayer* layer=PCRFunctionMusicLayer::create();
		layer->SetDelegate(this);
		this->addChild(layer,2);
	}
}

void PCRMapLayer::OnCloseLayer( CCLayer* layer )
{
	this->removeChild(layer);
}




