#include "GameHelper.h"

GameHelper::GameHelper()
{

}

GameHelper::~GameHelper()
{

}

vector<string> GameHelper::split( const string& ori , char ch )
{
	vector<string> ans;
	split(ori , ch , ans);
	return ans;
}

vector<string>& GameHelper::split( const string& ori , char ch , vector<string>& ans )
{
	istringstream iss(ori);
	string item;
	while(getline(iss , item , ch)) ans.push_back(item);
	return ans;
}

int GameHelper::getInt( const string &s )
{
	stringstream ss;
	int num;
	ss.str(s);
	ss>>num;
	return num;
}
