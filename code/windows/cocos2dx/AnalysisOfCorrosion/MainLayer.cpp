#include "MainLayer.h"

bool MainLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}
	//set main layer size
	this->setContentSize(Winsize);

	//add left layer
	interfaceLayer = InterfaceLayer::create();
	Common::setConstentSize_comparedWithAnother(this, interfaceLayer, __designLRratio, 1);
	addChild(interfaceLayer);

	//add right layer
	displayLayer = DisplayLayer::create();
	Common::setConstentSize_comparedWithAnother(this, displayLayer, 1- __designLRratio, 1);
	displayLayer->setPosition(interfaceLayer->getContentSize().width, 0);
	addChild(displayLayer);

	//connect two layers
	interfaceLayer->ConnectWithDisplayLayer(displayLayer);

	return true;
}


Scene* MainLayer::createscene() {
	Scene* scene = Scene::create();
	MainLayer* layer = MainLayer::create();
	scene->addChild(layer);
	return scene;
}

