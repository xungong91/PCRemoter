#ifndef _PCR_FUNCTION_SYSTEM_LAYER_H
#define _PCR_FUNCTION_SYSTEM_LAYER_H

#include "PCRFunctionBaseLayer.h"
class PCRFunctionSystemLayer:public PCRFunctionBaseLayer
{
public:
	CREATE_FUNC(PCRFunctionSystemLayer);
	bool init();
	void Slider_audio_Event(CCObject* Obj,TouchEventType type);
	void TextButton_down_Event(CCObject* Obj,TouchEventType type);
	void TextButton__escdown_Event(CCObject* Obj,TouchEventType type);
	void TextButton__restart_Event(CCObject* Obj,TouchEventType type);
	void TextButton__sleep_Event(CCObject* Obj,TouchEventType type);
	void Button_audio_up_Event(CCObject* Obj,TouchEventType type);
	void Button_audio_down_Event(CCObject* Obj,TouchEventType type);
	void Button_audio_pause_Event(CCObject* Obj,TouchEventType type);
	void TextButton__Esc_Event(CCObject* Obj,TouchEventType type);
	void TextButton__Schalt_Event(CCObject* Obj,TouchEventType type);
private:
};
#endif

