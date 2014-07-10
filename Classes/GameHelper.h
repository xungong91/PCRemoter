#ifndef _GAME_HELPER_H_
#define _GAME_HELPER_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class GameHelper
{
public:
	GameHelper();
	~GameHelper();
	static vector<string> split(const string& ori , char ch);
	static int getInt(const string &s);
private:
	static vector<string>& split(const string& ori , char ch , vector<string>& ans);
};
#endif