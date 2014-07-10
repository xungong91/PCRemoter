#ifndef _G_FILE_HELPER
#define _G_FILE_HELPER

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class KeyboardShortcuts
{
public:
	string TF_a;
	string TF_b;
	string TF_c;
	string TF_d;
	string TF_e;
	string TF_f;
	string TF_up;
	string TF_down;
	string TF_right;
	string TF_left;
	void Save();
	void Get();
};

class GFileHelper
{
public:
	void CreateOrOpen();
	void Create();
	static GFileHelper* Singleton();
	~GFileHelper();
	void SetIPandkey(const char* ip,const char* key);
protected:
	static GFileHelper* _GFileHelper;
	class CGarbo
	{  
	public:  
		~CGarbo()  
		{  
			if (GFileHelper::_GFileHelper)  
				delete GFileHelper::_GFileHelper;  
		}  
	};  
	static CGarbo Garbo;
	GFileHelper();
};
#endif