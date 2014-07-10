#ifndef _CONTROL_LAYER_H_
#define _CONTROL_LAYER_H_

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class ControlLayer : public CCLayerColor
{
public:
	ControlLayer();
	~ControlLayer();
	CREATE_FUNC(ControlLayer);
	bool init();
	void setControlColor( const string & msgData );
private:

};

#endif