#ifndef _DEFINES_H_
#define _DEFINES_H_
#include "cocos2d.h"
USING_NS_CC;

#define RECV_DATA_BUF_SZ				2048		//������
#define SEND_SEVER_MSG			 "SEND_SEVER_MSG"	
#define CONNECTION_PORT					8087		//���Ӷ˿�
#define CONNECTION_UDPPORT				8086		//���Ӷ˿�
//�����
#define ARROWKEYSLEFT			0x25
#define ARROWKEYSUP				0x26
#define ARROWKEYSRIGHT			0x27
#define ARROWKEYSDOWN			0x28
#define ARROWKEYSLEFTANDUP		0x21
#define ARROWKEYSUPANDRIGHT		0x22
#define ARROWKEYSRIGHTANDDOWN	0x23
#define ARROWKEYSDOWNANDLEFT	0x24
//����״̬
#define CONNECTION_SUCCESSFUL			0x01		//���ӳɹ�
#define CONNECTION_FAILURE				0x02		//����ʧ��
#define CONNECTION_NAT_UDP_CTS			0x03		//c->s �������ip�Ͷ˿�
#define CONNECTION_NAT_UDP_STC			0x04		//s->c �ظ�����ip�Ͷ˿�
#define CONNECTION_CONTROL				0x05		//�����ֻ�
#define CONNECTION_CONTROL_COLOR		0x06		//�����ֻ���ɫ
#define FUNCTION_SHUTDOWN				0x11		//�ػ�s
#define FUNCTION_CANCELSHUTDOWN			0x12		//ȡ���ػ�
#define FUNCTION_RESTART				0x13		//����
#define FUNCTION_DORMANCY				0x14		//����
#define FUNCTION_AUDIO_MUTE				0x15		//����
#define FUNCTION_AUDIO_UP				0x16		//��С����
#define FUNCTION_AUDIO_DOWN				0x17		//�Ӵ�����
#define FUNCTION_KEY_DOWN				0x18		//����ĳ��
#define FUNCTION_KEY_UP					0x19		//�ɿ�ĳ��
#define FUNCTION_ESC					0x1a		//�رյ�ǰ����
#define FUNCTION_SCHALT					0x1b		//�л�����
#define FUNCTION_PPT_UP					0x30		//ppt��һҳ
#define FUNCTION_PPT_DOWN				0x31		//ppt��һҳ
#define FUNCTION_PPT_FULLSCREEN			0x32		//pptȫ��
#define FUNCTION_PPT_QUITSCREEN			0x33		//ppt�˳�ȫ��

#define FUNCTION_CAMERA_START			0x40     //��������ͷ
#define	FUNCTION_CAMERA_CLOSE			0x41     //�ر�����ͷ
#define	FUNCTION_CAMERA_SENDIMAHE		0x42	//����ͼƬ
#define	FUNCTION_CAMERA_NOTIMAGE		0x43     //ȡ������ͼƬ
#define FUNCTION_MUSIC_OPEN				0x50	//��Ĭ�����ֲ�����
#define FUNCTION_MUSIC_MINI				0x51	//���㴰��
#define FUNCTION_MUSIC_LYC				0x52	//���
#define FUNCTION_MUSIC_PLAY				0x53	//��������
#define FUNCTION_MUSIC_NOTAUDIO			0x54	//����
#define FUNCTION_MUSIC_DOWNAUDIO		0x55	//��С
#define FUNCTION_MUSIC_UPAUDIO			0x56	//�Ӵ�����
#define FUNCTION_MUSIC_NEXTSONG			0x57	//��һ��
#define FUNCTION_MUSIC_ONSONG			0x58	//��һ��

#define CURTIME GetCurTime()
inline float GetCurTime(){
	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d(&now, NULL);  
	unsigned long millisecs = (now.tv_sec * 1000) + (now.tv_usec / 1000); 
	return (float)millisecs; 
};
#endif