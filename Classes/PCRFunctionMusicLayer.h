#ifndef _PCR_FUNCTION_MUSIC_LAYER_H
#define _PCR_FUNCTION_MUSIC_LAYER_H
#include "PCRFunctionBaseLayer.h"
class PCRFunctionMusicLayer:public PCRFunctionBaseLayer
{
public:
	CREATE_FUNC(PCRFunctionMusicLayer);
	bool init();
	void Slider_audio_Event(CCObject* Obj,TouchEventType type);
	void TextButton__Open_Event(CCObject* Obj,TouchEventType type);
	void TextButton__Mini_Event(CCObject* Obj,TouchEventType type);
	void TextButton__Lyrics_Event(CCObject* Obj,TouchEventType type);
	void TextButton__Play_Event(CCObject* Obj,TouchEventType type);
	void TextButton__NotAudio_Event(CCObject* Obj,TouchEventType type);
	void TextButton__AudioDown_Event(CCObject* Obj,TouchEventType type);
	void TextButton__AudioUp_Event(CCObject* Obj,TouchEventType type);
};
#endif

