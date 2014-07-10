#ifndef _PCR_CC_MSG_H_
#define _PCR_CC_MSG_H_

#include "cocos2d.h"
USING_NS_CC;
class PCRCCMsg:public CCObject
{
public:
	PCRCCMsg(){this->autorelease();};
	~PCRCCMsg(){};
	int m_msgType;
	void* data;
};
#endif

