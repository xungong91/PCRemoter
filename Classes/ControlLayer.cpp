#include "ControlLayer.h"
#include "GameHelper.h"

ControlLayer::ControlLayer()
{

}

ControlLayer::~ControlLayer()
{

}

bool ControlLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(255,255,0,255)))
	{
		return false;
	}

	return true;
}

void ControlLayer::setControlColor( const string & msgData )
{
	vector<string> colors = GameHelper::split(msgData, ' ');
		CCLayerColor::initWithColor(ccc4(GameHelper::getInt(colors[0]),
			GameHelper::getInt(colors[1]),
			GameHelper::getInt(colors[2]),
			colors.size() < 4 ? 255 : GameHelper::getInt(colors[3])));
}
