#ifndef _DEFINES_H_
#define _DEFINES_H_
#include "cocos2d.h"
USING_NS_CC;

#define RECV_DATA_BUF_SZ				2048		//缓冲区
#define SEND_SEVER_MSG			 "SEND_SEVER_MSG"	
#define CONNECTION_PORT					8087		//连接端口
#define CONNECTION_UDPPORT				8086		//连接端口
//方向键
#define ARROWKEYSLEFT			0x25
#define ARROWKEYSUP				0x26
#define ARROWKEYSRIGHT			0x27
#define ARROWKEYSDOWN			0x28
#define ARROWKEYSLEFTANDUP		0x21
#define ARROWKEYSUPANDRIGHT		0x22
#define ARROWKEYSRIGHTANDDOWN	0x23
#define ARROWKEYSDOWNANDLEFT	0x24
//连接状态
#define CONNECTION_SUCCESSFUL			0x01		//连接成功
#define CONNECTION_FAILURE				0x02		//连接失败
#define CONNECTION_NAT_UDP_CTS			0x03		//c->s 请求监听ip和端口
#define CONNECTION_NAT_UDP_STC			0x04		//s->c 回复监听ip和端口
#define CONNECTION_CONTROL				0x05		//控制手机
#define CONNECTION_CONTROL_COLOR		0x06		//控制手机颜色
#define FUNCTION_SHUTDOWN				0x11		//关机s
#define FUNCTION_CANCELSHUTDOWN			0x12		//取消关机
#define FUNCTION_RESTART				0x13		//重启
#define FUNCTION_DORMANCY				0x14		//休眠
#define FUNCTION_AUDIO_MUTE				0x15		//静音
#define FUNCTION_AUDIO_UP				0x16		//减小音量
#define FUNCTION_AUDIO_DOWN				0x17		//加大音量
#define FUNCTION_KEY_DOWN				0x18		//按下某键
#define FUNCTION_KEY_UP					0x19		//松开某件
#define FUNCTION_ESC					0x1a		//关闭当前程序
#define FUNCTION_SCHALT					0x1b		//切换程序
#define FUNCTION_PPT_UP					0x30		//ppt上一页
#define FUNCTION_PPT_DOWN				0x31		//ppt下一页
#define FUNCTION_PPT_FULLSCREEN			0x32		//ppt全屏
#define FUNCTION_PPT_QUITSCREEN			0x33		//ppt退出全屏

#define FUNCTION_CAMERA_START			0x40     //启动摄像头
#define	FUNCTION_CAMERA_CLOSE			0x41     //关闭摄像头
#define	FUNCTION_CAMERA_SENDIMAHE		0x42	//发送图片
#define	FUNCTION_CAMERA_NOTIMAGE		0x43     //取消发送图片
#define FUNCTION_MUSIC_OPEN				0x50	//打开默认音乐播放器
#define FUNCTION_MUSIC_MINI				0x51	//迷你窗口
#define FUNCTION_MUSIC_LYC				0x52	//歌词
#define FUNCTION_MUSIC_PLAY				0x53	//播放音乐
#define FUNCTION_MUSIC_NOTAUDIO			0x54	//静音
#define FUNCTION_MUSIC_DOWNAUDIO		0x55	//减小
#define FUNCTION_MUSIC_UPAUDIO			0x56	//加大音量
#define FUNCTION_MUSIC_NEXTSONG			0x57	//下一首
#define FUNCTION_MUSIC_ONSONG			0x58	//上一首

#define CURTIME GetCurTime()
inline float GetCurTime(){
	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d(&now, NULL);  
	unsigned long millisecs = (now.tv_sec * 1000) + (now.tv_usec / 1000); 
	return (float)millisecs; 
};
#endif