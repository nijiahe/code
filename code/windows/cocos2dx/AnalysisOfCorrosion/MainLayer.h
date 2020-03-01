#pragma once

#include "Common.h"
#include "InterfaceLayer.h"
#include "DisplayLayer.h"

class MainLayer :public LayerColor
{
public:
	CREATE_FUNC(MainLayer);
	bool init();
	static Scene* createscene();
	
	InterfaceLayer* interfaceLayer;
	DisplayLayer* displayLayer;
	ProgressTimer * _process_timer;
	int _total_file_num;
};