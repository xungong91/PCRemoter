#ifndef _PCR_CLIENT_H_
#define _PCR_CLIENT_H_

#include "ODSocket.h"
#include "pthread.h"

class PCRMsg
{
public:
	int type;
	char* data;
	int len;
};

class PCRClient
{
public:
	static PCRClient* Singleton();
	~PCRClient();
	pthread_t thread1;
	static bool m_bShutdownConnection;
	static void* ConnectionReceiveData(void* args);	
	void Connection(const char* ip, const char* port);
	void connection(const char* ip);
	void OnNetMessage(char* data,int len);
	int SendMsg(PCRMsg *pcrmsg);
	int SendUdpMsg(PCRMsg *pcrmsg);
	ODSocket m_client;
	ODSocket m_udpclient;
	sockaddr_in svraddr;
	int UdpReve(char* data);
protected:
	static PCRClient *m_PCRClient;
	PCRClient();
	class CGarbo
	{  
	public:  
		~CGarbo()  
		{  
			if (PCRClient::m_PCRClient)  
				delete PCRClient::m_PCRClient;  
		}  
	};  
	static CGarbo Garbo;
	void RecvSeverMsg(PCRMsg* data);
	void on_CONNECTION_SUCCESSFUL(char* data,int len);
	void on_CONNECTION_FAILURE(char* data,int len);
	void on_CONNECTION_NAT_UDP_STC(char* data,int len);
	void on_CONNECTION_CONTROL(char* data,int len);
	void on_CONNECTION_CONTROL_COLOR(char* data,int len);
};
#endif