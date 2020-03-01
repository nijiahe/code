#ifndef __Rinkint_List_Layer_H__
#define __Rinkint_List_Layer_H__

#include "Common.h"
#include "network/HttpClient.h"

using namespace network;

#include "Common.h"

class Rinkint_List_Layer :public Layer
{
public:
	bool init(int score);
	static Rinkint_List_Layer * create(int score);

	void main_menu_callfunc(Ref * ref);
	void HttoResponse(HttpClient* client, HttpResponse* response);

	Vector<Label *> _label_vec;
	int _score = 0;
};

#endif