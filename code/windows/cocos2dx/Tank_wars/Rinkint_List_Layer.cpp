#include "Rinkint_List_Layer.h"
#include "Start_Layer.h"

bool Rinkint_List_Layer::init(int score)
{
	if (!Layer::init())
	{
		return false;
	}
	_score = score;
	HttpClient * client = HttpClient::getInstance();

	HttpRequest * request = new HttpRequest();
	char sendstr[1024];
	sprintf(sendstr, "http://192.168.43.23/cgi-bin/Tank_War/Tank_Rinking.cgi?name=SM_G9350&score=%d", score);
	request->setUrl(sendstr);//服务器地址
	request->setRequestType(HttpRequest::Type::GET);//请求类型,多线程
	request->setResponseCallback(CC_CALLBACK_2(Rinkint_List_Layer::HttoResponse, this));
	client->send(request);
	request->release();

	Label * tittle = Label::createWithTTF("Rinking List", "fonts/arial.ttf", 50);
	tittle->setColor(Color3B(255,255,100));
	addChild(tittle);
	tittle->setPosition(Winsize.width*0.5, Winsize.height*0.9);

	for (int i = 0; i < 10; i++)
	{
		Label * label = Label::createWithTTF("-", "fonts/arial.ttf", 20);
		addChild(label);
		_label_vec.pushBack(label);
		label->setPosition(Winsize.width*0.5, Winsize.height*0.8 - i * Winsize.height*0.06);
	}


	MenuItem * item = MenuItemFont::create("Main Menu", CC_CALLBACK_1(Rinkint_List_Layer::main_menu_callfunc, this));
	Menu * menu = Menu::create(item, NULL);
	menu->setPosition(Winsize.width*0.5, Winsize.height*0.15);
	addChild(menu);
	
	return true;
}

void Rinkint_List_Layer::HttoResponse(HttpClient* client, HttpResponse* response)
{
	if (!response->isSucceed())
	{
		CCLOG("response error: %s", response->getErrorBuffer());//错误信息
		return;
	}

	std::vector<char> * vec = response->getResponseData();//服务器信息
	std::string str;
	std::vector<char>::iterator ibegin = vec->begin();
	for (; ibegin != vec->end(); ibegin++)
	{
		str.push_back(*ibegin);
	}
	
	char receive_str[2048];
	sprintf(receive_str,"%s", str.c_str());
	int receive_num = 0;
	char * walk = receive_str;
	while (*walk != '\0')
	{
		if (*walk == '&')
		{
			receive_num++;
		}
		walk++;
	}
	char * username;
	char * score;
	char label_str[100];
	for (int i = 0; i < (receive_num+1)/2; i++)
	{
		if (i == 0)
		{
			username = strtok(receive_str, "&");
		}
		else
		{
			username = strtok(NULL, "&");
		}
		score = strtok(NULL, "&");
		sprintf(label_str, "%s:%s", username, score);
		_label_vec.at(i)->setString(label_str);
	}
}

void Rinkint_List_Layer::main_menu_callfunc(Ref * ref)
{
	Director::getInstance()->resume();
	Start_Layer * layer = Start_Layer::create();
	Scene * scene = Common::createscene(layer);
	Director::getInstance()->replaceScene(scene);
}

Rinkint_List_Layer * Rinkint_List_Layer::create(int score)
{
	Rinkint_List_Layer * pRet = new Rinkint_List_Layer;
	if (pRet&&pRet->init(score))
	{
		pRet->autorelease();
	}
	else
	{
		delete(pRet);
		pRet = NULL;
	}
	return pRet;
}