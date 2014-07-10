#include "PCRLoginLayer.h"
#include "PCRClient.h"
#include "Defines.h"
#include <string>
using namespace std;
bool PCRLoginLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}
void PCRLoginLayer::onEnter()
{
	CCLayer::onEnter();
	m_uilayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI_Login/RemoterUI_Login.ExportJson"));
	m_uilayer->addWidget(UI_Dialog);
	this->addChild(m_uilayer,1);

	TextField_Key=(UITextField*)m_uilayer->getWidgetByName("TextField_Key");
	TextField_IP=(UITextField*)m_uilayer->getWidgetByName("TextField_IP");
	string ip= CCUserDefault::sharedUserDefault()->getStringForKey("ip");
	string key= CCUserDefault::sharedUserDefault()->getStringForKey("key");
	if (ip.length()>0&&key.length()>0)
	{
		TextField_Key->setText(key.c_str());
		TextField_IP->setText(ip.c_str());
	}
	UITextButton* TextButton_Enter=(UITextButton*)m_uilayer->getWidgetByName("TextButton_Enter");
	UIWidget* Button_Close=(UIWidget*)m_uilayer->getWidgetByName("Button_Close");
	TextButton_Enter->addTouchEventListener(this,toucheventselector(PCRLoginLayer::TextButton_Enter_Event));
	Button_Close->addTouchEventListener(this,toucheventselector(PCRLoginLayer::Button_Close_Event));
}
void PCRLoginLayer::onExit()
{
	CCLayer::onExit();
}

void PCRLoginLayer::TextButton_Enter_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		string s=TextField_Key->getStringValue();
		int key;
		stringstream ss;
		ss.str(s.c_str());
		ss>>key;
		char* buffer=(char*)&key;
		PCRClient::Singleton()->Connection(TextField_IP->getStringValue(), buffer);
	}
}

void PCRLoginLayer::Button_Close_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		CCDirector::sharedDirector()->end();
	}
}
