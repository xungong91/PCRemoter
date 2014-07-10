#include "PCRMsgSendQueue.h"

void PCRMsgSendQueue::postMsg( PCRMsg* pcrmsg )
{
	pthread_create(&thread1,NULL,SendData,pcrmsg);//创建线程A  
}

PCRMsgSendQueue::PCRMsgSendQueue()
{

}

PCRMsgSendQueue::~PCRMsgSendQueue()
{

}
PCRMsgSendQueue* PCRMsgSendQueue::_PCRMsgSendQueue=NULL;
PCRMsgSendQueue* PCRMsgSendQueue::Singleton()
{
	if (_PCRMsgSendQueue==NULL)
	{
		_PCRMsgSendQueue=new PCRMsgSendQueue();
	}
	return _PCRMsgSendQueue;
}

void* PCRMsgSendQueue::SendData( void* args )
{
	PCRMsg* pcrmsg=(PCRMsg*)args;
	PCRClient::Singleton()->SendMsg(pcrmsg);
	return NULL;
}
