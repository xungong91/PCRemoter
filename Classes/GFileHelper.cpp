#include "GFileHelper.h"
GFileHelper::GFileHelper()
{

}

GFileHelper::~GFileHelper()
{
	_GFileHelper=NULL;
}
GFileHelper::CGarbo GFileHelper::Garbo;
GFileHelper* GFileHelper::_GFileHelper=NULL;
GFileHelper* GFileHelper::Singleton()
{
	if (_GFileHelper==NULL)
	{
		_GFileHelper=new GFileHelper();
	}
	return _GFileHelper;
}

void GFileHelper::CreateOrOpen()
{
	bool isExist= CCUserDefault::sharedUserDefault()->getBoolForKey("IsFile");
	if (!isExist)
	{
		Create();
	}
}

void GFileHelper::Create()
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("IsFile", true);
	CCUserDefault::sharedUserDefault()->setStringForKey("ip", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("key", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_a", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_b", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_c", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_d", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_e", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_f", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_up", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_down", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_right", "");
	CCUserDefault::sharedUserDefault()->setStringForKey("TF_left", "");
}
void GFileHelper::SetIPandkey( const char* ip,const char* key )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("ip",ip);
	CCUserDefault::sharedUserDefault()->setStringForKey("key",key);
}


void KeyboardShortcuts::Save()
{
#define SET_TFTEXT(TF_NAME) \
	CCUserDefault::sharedUserDefault()->setStringForKey(#TF_NAME,TF_NAME)
	SET_TFTEXT(TF_a);
	SET_TFTEXT(TF_b);
	SET_TFTEXT(TF_c);
	SET_TFTEXT(TF_d);
	SET_TFTEXT(TF_e);
	SET_TFTEXT(TF_f);
	SET_TFTEXT(TF_up);
	SET_TFTEXT(TF_down);
	SET_TFTEXT(TF_left);
	SET_TFTEXT(TF_right);
}

void KeyboardShortcuts::Get()
{
#define GET_TFTEXT(TF_NAME) \
	TF_NAME=CCUserDefault::sharedUserDefault()->getStringForKey(#TF_NAME)
	GET_TFTEXT(TF_a);
	GET_TFTEXT(TF_b);
	GET_TFTEXT(TF_c);
	GET_TFTEXT(TF_d);
	GET_TFTEXT(TF_e);
	GET_TFTEXT(TF_f);
	GET_TFTEXT(TF_up);
	GET_TFTEXT(TF_down);
	GET_TFTEXT(TF_left);
	GET_TFTEXT(TF_right);
}
