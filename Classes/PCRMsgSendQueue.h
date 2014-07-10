#ifndef _PCR_MSG_SEND_QUEUE_H_
#define _PCR_MSG_SEND_QUEUE_H_

#include "PCRClient.h"
#include <pthread.h>  

using namespace std;
class PCRMsgSendQueue
{
public:
	pthread_t thread1;
	static void* SendData(void* args);	
	void postMsg(PCRMsg *pcrmsg);  
	static PCRMsgSendQueue* Singleton();
protected:
	static PCRMsgSendQueue* _PCRMsgSendQueue;
	PCRMsgSendQueue();
	~PCRMsgSendQueue();
};

#endif

