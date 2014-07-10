#include "PCRFunctionBaseLayer.h"
#include "PCRMsgSendQueue.h"
PCRFunctionBaseLayer::PCRFunctionBaseLayer()
{
	
}

PCRFunctionBaseLayer::~PCRFunctionBaseLayer()
{
}

bool PCRFunctionBaseLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}
void PCRFunctionBaseLayer::SetDelegate( PCRFunctionDelegate* _delegate )
{
	this->m_delegate=_delegate;
}
void PCRFunctionBaseLayer::Button_close_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		m_delegate->OnCloseLayer(this);
	}
}
void PCRFunctionBaseLayer::SendMsg( int type,char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->type=type;
	pcrmsg->data=data;
	pcrmsg->len=len;
	PCRClient::Singleton()->SendUdpMsg(pcrmsg);
	//PCRMsgSendQueue::Singleton()->postMsg(pcrmsg);
}

void PCRFunctionBaseLayer::SendTcpMsg( int type,char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->type=type;
	pcrmsg->data=data;
	pcrmsg->len=len;
	PCRClient::Singleton()->SendMsg(pcrmsg);
}
