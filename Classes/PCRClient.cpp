#include "PCRClient.h"
#include "MTNotificationQueue.h"
#include "Defines.h"
#include "PCRCCMsg.h"
#include <iomanip>
#include <string>
using namespace std;
PCRClient::PCRClient()
{

}

PCRClient::~PCRClient()
{
	m_PCRClient=NULL;
	m_bShutdownConnection=true;
}
PCRClient::CGarbo PCRClient::Garbo;
PCRClient* PCRClient::m_PCRClient=NULL;
PCRClient* PCRClient::Singleton()
{
	if (m_PCRClient==NULL)
	{
		m_PCRClient=new PCRClient(); 
	}
	return m_PCRClient;
}
void PCRClient::Connection( const char* ip, const char* key )
{
	m_client.Init();
	m_client.Create(AF_INET,SOCK_STREAM,0);
	bool isConnect=m_client.Connect(ip,CONNECTION_PORT);
	if(isConnect)
	{
		m_udpclient.Init();
		m_udpclient.Create(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		m_udpclient.Bind(CONNECTION_UDPPORT);
		svraddr.sin_family = AF_INET;
		svraddr.sin_addr.s_addr=inet_addr(ip);
		svraddr.sin_port = htons(CONNECTION_PORT);

		pthread_create(&thread1,NULL,ConnectionReceiveData,this);//创建线程A  
		m_client.Send(key,strlen(key)+1);
	}
	else
	{
		CCMessageBox("sever not open?","error");
	}
}

void PCRClient::connection( const char* ip )
{
	m_client.Init();
	m_client.Create(AF_INET,SOCK_STREAM,0);
	bool isConnect=m_client.Connect(ip,CONNECTION_PORT);
	if (isConnect)
	{
		pthread_create(&thread1,NULL,ConnectionReceiveData,this);//创建线程A  
	}
}

bool PCRClient::m_bShutdownConnection=false;

void* PCRClient::ConnectionReceiveData( void* args )
{
	PCRClient* client=(PCRClient*)args;
	int nExitReason = -1;
	int nRecv = 0;
	char receivedata[RECV_DATA_BUF_SZ] = "\0";
	while (true)
	{
		if (m_bShutdownConnection == true) {
			break;
		}

		nRecv=client->m_client.Recv(receivedata,RECV_DATA_BUF_SZ);

		if (nRecv > 0) 
		{
			client->OnNetMessage(receivedata, nRecv);
		} else if (nRecv == 0) {
			nExitReason = 1;
			break;
		} else {
			nExitReason = 2;
			break;
		}
	}
	client->m_client.Close();
	client->m_client.Clean();
	return NULL;
}
void PCRClient::RecvSeverMsg(PCRMsg* data )
{
	PCRCCMsg* msg=new PCRCCMsg();
	msg->retain();
	msg->data=data;
	MTNotificationQueue::sharedInstance()->postNotification(SEND_SEVER_MSG,msg);
}
int PCRClient::SendMsg(PCRMsg *pcrmsg)
{
	int type =pcrmsg->type;
	char* data=pcrmsg->data;
	int len=pcrmsg->len; 

	int length=1+2+len;
	char* buffer=new char[length];
	//类型
	buffer[0]=type;
	//数据长度
	char* lendata=(char*)(&len);
	buffer[1]=lendata[0];
	buffer[2]=lendata[1];
	//数据
	memcpy(buffer+3,data,len);
	//发送
	int result= m_client.Send(buffer,length);
	delete buffer;
	delete pcrmsg;
	return result;
}
int PCRClient::SendUdpMsg(PCRMsg *pcrmsg)
{
	int type =pcrmsg->type;
	char* data=pcrmsg->data;
	int len=pcrmsg->len; 

	int length=1+2+len;
	char* buffer=new char[length];
	//类型
	buffer[0]=type;
	//数据长度
	char* lendata=(char*)(&len);
	buffer[1]=lendata[0];
	buffer[2]=lendata[1];
	//数据
	memcpy(buffer+3,data,len);
	//发送
	int result= m_udpclient.Sendto(buffer,length,(sockaddr*)&svraddr,sizeof(sockaddr_in));
	delete buffer;
	delete pcrmsg;
	return result;
}
int PCRClient::UdpReve( char* data )
{
	int result= m_udpclient.Recv(data,10240);
	return result;
}
void PCRClient::OnNetMessage( char* data,int len )
{
	int nParsedLen = 0;     // 分析过数据的长度
	int nMsgCode = 0;       // 消息码
	int nMsgBodyLen = 0;    // 消息体长度  参数2
	char* pMsgBody = NULL;  // 消息体数据起始指针
	int   msgcount = 0;		// 已经解析过的合法数据
	while (nParsedLen < len) 
	{
		if (nParsedLen + 2 >= len) {
			//消息结构不合法。已解析 %d 个合法消息"), msgcount);
			return;
		}
		/*char strlen[]={data[nParsedLen+1],data[nParsedLen+2]};
		nMsgBodyLen=atoi(strlen);*/
		nMsgBodyLen=	data[nParsedLen + 1] | (data[nParsedLen + 2])<< 8;

		// 1个字节消息码，2个字节消息体长度，nMsgBodyLen个字节消息体
		if (nParsedLen + 1 + 2 + nMsgBodyLen > len)
		{
			//消息结构不合法。已解析 %d 个合法消息"), msgcount);
			return;
		}
		nMsgCode = data[nParsedLen];
		pMsgBody = data + nParsedLen + 1 + 2;  //参数1

		nParsedLen += (1 + 2 + nMsgBodyLen);
		msgcount++;

#define ON_NMSG_BREAK(NMSG_NAME) \
case NMSG_NAME: { on_ ## NMSG_NAME (pMsgBody, nMsgBodyLen); break; }

		switch (nMsgCode)
		{
			ON_NMSG_BREAK(CONNECTION_SUCCESSFUL)
			ON_NMSG_BREAK(CONNECTION_FAILURE)
			ON_NMSG_BREAK(CONNECTION_NAT_UDP_STC)
			ON_NMSG_BREAK(CONNECTION_CONTROL)
			ON_NMSG_BREAK(CONNECTION_CONTROL_COLOR)
		default:
			break;
		}
	}
}
void PCRClient::on_CONNECTION_SUCCESSFUL( char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->data=data;
	pcrmsg->len=len;
	pcrmsg->type=CONNECTION_SUCCESSFUL;
	RecvSeverMsg(pcrmsg);
}

void PCRClient::on_CONNECTION_FAILURE( char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->data=data;
	pcrmsg->len=len;
	pcrmsg->type=CONNECTION_FAILURE;
	RecvSeverMsg(pcrmsg);
}

void PCRClient::on_CONNECTION_NAT_UDP_STC( char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->data=data;
	pcrmsg->len=len;
	pcrmsg->type=CONNECTION_NAT_UDP_STC;
	RecvSeverMsg(pcrmsg);
}

void PCRClient::on_CONNECTION_CONTROL( char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->data=data;
	pcrmsg->len=len;
	pcrmsg->type=CONNECTION_CONTROL;
	RecvSeverMsg(pcrmsg);
}

void PCRClient::on_CONNECTION_CONTROL_COLOR( char* data,int len )
{
	PCRMsg* pcrmsg=new PCRMsg();
	pcrmsg->data=data;
	pcrmsg->len=len;
	pcrmsg->type=CONNECTION_CONTROL_COLOR;
	RecvSeverMsg(pcrmsg);
}


