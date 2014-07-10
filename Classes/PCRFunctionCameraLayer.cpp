#include "PCRFunctionCameraLayer.h"
#include "PCRMainScene.h"
#include "PCRClient.h"
bool PCRFunctionCameraLayer::init()
{
	if (!PCRFunctionBaseLayer::init())
	{
		return false;
	}
	m_uilayer = UILayer::create();
	UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("RemoterUI/RemoterUI_Camera.json"));
	m_uilayer->addWidget(UI_Dialog);
	this->addChild(m_uilayer,1);

	ADD_WIDGRT_EVENT(Button_close,PCRFunctionCameraLayer)
	ADD_WIDGRT_EVENT(TextButton_Open,PCRFunctionCameraLayer)
	ADD_WIDGRT_EVENT(TextButton_Close,PCRFunctionCameraLayer)
	ADD_WIDGRT_EVENT(TextButton_Recv,PCRFunctionCameraLayer)
	ADD_WIDGRT_EVENT(TextButton_Stop,PCRFunctionCameraLayer)
	sprite=CCSprite::create();
	sprite->setContentSize(CCSizeMake(320,240));
	sprite->setPosition(ccp(160,160));
	this->addChild(sprite,2);

	return true;
}

void PCRFunctionCameraLayer::TextButton_Open_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendMsg(FUNCTION_CAMERA_START,NULL,0);
	}
}
void PCRFunctionCameraLayer::TextButton_Close_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		SendMsg(FUNCTION_CAMERA_CLOSE,NULL,0);
	}
}
void PCRFunctionCameraLayer::TextButton_Recv_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		char* data=PCRMainScene::Singleton()->m_ip;
		int lenght=strlen(data);
		SendMsg(FUNCTION_CAMERA_SENDIMAHE,data,lenght);

		this->unschedule(schedule_selector(PCRFunctionCameraLayer::SetImageCB));
		this->schedule(schedule_selector(PCRFunctionCameraLayer::SetImageCB),0.05);
	}
}
void PCRFunctionCameraLayer::SetImageCB( float dt )
{
	char recvBuf[10240] = "";
	int a=PCRClient::Singleton()->UdpReve(recvBuf);
	//int a= m_udpsever.Recvfrom(recvBuf,10240,(struct sockaddr*)&svraddr,sizeof(sockaddr_in));
	CCImage* image=new CCImage();
	image->initWithImageData(recvBuf,a,CCImage::kFmtJpg,320,240,8);
	CCTexture2D * tex = new CCTexture2D();
	tex->initWithImage(image);
	CC_SAFE_RELEASE(image);
	CC_SAFE_RELEASE(sprite->getTexture());
	sprite->initWithTexture(tex);
}
void PCRFunctionCameraLayer::TextButton_Stop_Event( CCObject* Obj,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		this->unschedule(schedule_selector(PCRFunctionCameraLayer::SetImageCB));
		SendMsg(FUNCTION_CAMERA_NOTIMAGE,NULL,0);
		//pthread_create(&thread1,NULL,ConnectionReceiveData,this);//创建线程A  
	}
}
void PCRFunctionCameraLayer::RecvieCB( float dt )
{

}

void PCRFunctionCameraLayer::onEnter()
{
	CCLayer::onEnter();
	SendMsg(FUNCTION_CAMERA_START,NULL,0);
}

void PCRFunctionCameraLayer::onExit()
{
	SendMsg(FUNCTION_CAMERA_CLOSE,NULL,0);
	CC_SAFE_RELEASE(sprite->getTexture());
	CCLayer::onExit();
}



