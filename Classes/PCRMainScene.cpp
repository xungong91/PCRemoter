#include "PCRMainScene.h"
#include "Defines.h"
#include "MTNotificationQueue.h"
#include "PCRCCMsg.h"
#include "GFileHelper.h"
#include "PCRClient.h"

PCRMainScene* PCRMainScene::m_PCRMainScene=NULL;
PCRMainScene::CGarbo PCRMainScene::cgarbo;
PCRMainScene* PCRMainScene::Singleton()
{
	if (m_PCRMainScene==NULL)
	{
		m_PCRMainScene=new PCRMainScene();
	}
	return m_PCRMainScene;
}

PCRMainScene::PCRMainScene()
{
	GFileHelper::Singleton()->CreateOrOpen();
	m_ip=new char[24];
}

PCRMainScene::~PCRMainScene()
{
	delete m_ip;
	m_PCRMainScene=NULL;
}
bool PCRMainScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	return true;
}
void PCRMainScene::onEnter()
{
	CCScene::onEnter();
	CCObject *obj1=NULL;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(PCRMainScene::SeverSendMsgCB),SEND_SEVER_MSG,obj1);   
	loginlayer=PCRLoginLayer::create();
	this->addChild(loginlayer);
	this->schedule(schedule_selector(PCRMainScene::NotificationCB),0.2f);
}

void PCRMainScene::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
	ObjectFactory::getInstance()->destroyInstance();
	CCScene::onExit();
}
void PCRMainScene::GotoMapLayer()
{
	this->removeChild(loginlayer);
	maplayer=PCRMapLayer::create();
	this->addChild(maplayer);
}

void PCRMainScene::GotoLoginLayer()
{
	this->removeChild(maplayer);
	loginlayer=PCRLoginLayer::create();
	this->addChild(loginlayer);
}

void PCRMainScene::GotoControlLayer()
{
	this->removeChild(loginlayer);
	mControlLayer = ControlLayer::create();
	this->addChild(mControlLayer);
}

void PCRMainScene::NotificationCB( float dt )
{
	MTNotificationQueue::sharedInstance()->postNotifications(dt);
}
void PCRMainScene::SeverSendMsgCB( CCObject* obj )
{
	PCRCCMsg* msg=(PCRCCMsg*)obj;
	PCRMsg* pcrmsg=(PCRMsg*)msg->data;
	const string &msgData = pcrmsg->data;
	int type=pcrmsg->type;
	int length=pcrmsg->len;
	switch (type)
	{
	case CONNECTION_SUCCESSFUL:
		GFileHelper::Singleton()->SetIPandkey(loginlayer->TextField_IP->getStringValue(),loginlayer->TextField_Key->getStringValue());
		//PCRFunctionBaseLayer::SendMsg(CONNECTION_NAT_UDP_CTS,NULL,0);
		GotoMapLayer();
		break;
	case CONNECTION_FAILURE:
		CCMessageBox("connection failure","error");
		break;
	case CONNECTION_NAT_UDP_STC:
		{
			string ipendpoint = msgData;
			int key=ipendpoint.find(':',0);
			string strip=ipendpoint.substr(0,key);
			string strport=ipendpoint.substr(key+1,ipendpoint.length()-key+1);
			//m_port
			strcpy(m_ip,strip.c_str());
			m_port=atoi(strport.c_str());
		}
		break;
	case CONNECTION_CONTROL:
		{
			GFileHelper::Singleton()->SetIPandkey(loginlayer->TextField_IP->getStringValue(),loginlayer->TextField_Key->getStringValue());
			GotoControlLayer();
		}
		break;
	case CONNECTION_CONTROL_COLOR:
		{
			mControlLayer->setControlColor(msgData);
		}
		break;
	default:
		break;
	}
	CC_SAFE_DELETE(pcrmsg);
	CC_SAFE_RELEASE(msg);
}

