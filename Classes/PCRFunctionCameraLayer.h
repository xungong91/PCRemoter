#ifndef _PCR_FUNCTION_CAMERA_LAYER_H_
#define _PCR_FUNCTION_CAMERA_LAYER_H_

#include "PCRFunctionBaseLayer.h"
#include "ODSocket.h"
#include "pthread.h"
#include <vector>

using namespace std;

class ImageBag
{
public:
	char* data;
	int length;
};

class PCRFunctionCameraLayer:public PCRFunctionBaseLayer
{
public:
	CREATE_FUNC(PCRFunctionCameraLayer);
	bool init();
	ODSocket m_udpsever;
	pthread_t thread1;
	static void* ConnectionReceiveData(void* args);	
	void RecvieCB(float dt);

	void TextButton_Open_Event(CCObject* Obj,TouchEventType type);
	void TextButton_Close_Event(CCObject* Obj,TouchEventType type);
	void TextButton_Recv_Event(CCObject* Obj,TouchEventType type);
	void TextButton_Stop_Event(CCObject* Obj,TouchEventType type);
	void SetImageCB(float dt);
	virtual void onEnter();
	virtual void onExit();
	static vector<ImageBag*> m_vertor;  
	CCSprite* sprite;
private:
};
#endif


