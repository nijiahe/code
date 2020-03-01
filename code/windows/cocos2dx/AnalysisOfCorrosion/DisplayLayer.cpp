#include "DisplayLayer.h"
#include "CorrosionAlgorithm.h"

extern int _ttfSize;

//#define MULTITHREAD 1

const char* DisplayLayer::mes = nullptr;
EditBox* DisplayLayer::_message1 = nullptr;
EditBox* DisplayLayer::_message2 = nullptr;

bool DisplayLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(250, 250, 250, 255)))
	{
		return false;
	}
	dics = __Dictionary::createWithContentsOfFile(__Chinese_XML);
	addItems();
	
	set2DAnalysisModel();
	set1DAnalysisModel();

	addTouchListen();

	check_platform();

#ifdef MULTITHREAD
	#ifdef _WIN32
		std::thread thread(DisplayLayer::thread_LOG);
		thread.detach();
	#endif
#endif

	return true;
}

void DisplayLayer::addItems() {
	//set teh diagram
	_chromaticityDiagram = Sprite::create("button/default.png");
	_chromaticityDiagram->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_chromaticityDiagram->setContentSize(Size(Winsize.width*(1 - __designLRratio) - 2 * __designDisplayWidthGap,
		Winsize.height - 3 * __designDisplayHeightGap));
	_chromaticityDiagram->setPosition(Winsize.width*(1-__designLRratio)- _chromaticityDiagram->getContentSize().width-__designEdgeGap
		, Winsize.height - _chromaticityDiagram->getContentSize().height - __designEdgeGap);
	addChild(_chromaticityDiagram);
	

	//set diagram boundingbox and the x-y axis
	DrawNode* drawnode = DrawNode::create();
	this->addChild(drawnode);
	drawnode->drawRect(_chromaticityDiagram->getPosition(), Vec2(_chromaticityDiagram->getPosition().x + _chromaticityDiagram->getContentSize().width, _chromaticityDiagram->getPosition().y + _chromaticityDiagram->getContentSize().height), Color4F(Color3B::BLACK,1));

	slider = ControlSlider::create("button/sliderTrack.png", "button/sliderProgress.png", "button/sliderThumb.png");
	slider->setContentSize(Size(_chromaticityDiagram->getContentSize().width*0.4, _ttfSize));
	slider->setPosition(_chromaticityDiagram->getPosition().x, _chromaticityDiagram->getPosition().y - slider->getContentSize().height- _ttfSize * 1.2);
	slider->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	slider->setMaximumAllowedValue(__MaxYear);
	slider->setMinimumAllowedValue(0);
	slider->setMaximumValue(__MaxYear);//设置最右边的值是多少
	slider->setMinimumValue(0);//设置最左边的值是多少
	slider->setValue(0);
	slider->addTargetWithActionForControlEvents(this, Control::Handler(&DisplayLayer::slider_call_back), Control::EventType::VALUE_CHANGED);
	addChild(slider);

	slide_num = EditBox::create(Size(_chromaticityDiagram->getContentSize().width/10, slider->getContentSize().height), "button/checkbox-unchecked.png");
	slide_num->setText("0");
	slide_num->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	slide_num->setPosition(
		Common::shift(slider->getPosition(), _chromaticityDiagram->getContentSize().width / 2, 0)
	);
	slide_num->setFontName(__Chinese_TTF);
	slide_num->setMaxLength(3);
	slide_num->setInputMode(EditBox::InputMode::DECIMAL);
	slide_num->setFontColor(Color3B::BLACK);
	addChild(slide_num); 

	word = Label::createWithTTF(dics->valueForKey("year")->getCString(), __Chinese_TTF, slide_num->getContentSize().height);
	word->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	word->setPosition(
		Common::shift(slide_num->getPosition(), _chromaticityDiagram->getContentSize().width / 10, 0)
	);
	addChild(word);

	yes = Button::create("button/button_background_normal.png", "button/button_background_pressed.png", "qihoo_button_orange_disabled.9.png");
	yes->setTitleText(dics->valueForKey("yes")->getCString());
	yes->setTitleFontSize(_ttfSize);
	yes->setTitleColor(Color3B::BLACK);
	yes->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	yes->ignoreContentAdaptWithSize(false);
	yes->setContentSize(Size(_chromaticityDiagram->getContentSize().width / 5, slide_num->getContentSize().height));
	yes->setPosition(Common::shift(word->getPosition(), word->getContentSize().width+ _chromaticityDiagram->getContentSize().width / 10, 0));
	addChild(yes);

	yes->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			__String* str = __String::create(slide_num->getText());
			slider->setValue(str->intValue());
			showYear(str->intValue());
		}
	});
	//words label
	_x_PixMessage = Label::createWithTTF(dics->valueForKey("_x_PixMessage")->getCString(), __Chinese_TTF, 24);
	_x_PixMessage->setContentSize(Size(_chromaticityDiagram->getContentSize().width*0.20, _ttfSize));
	_x_PixMessage->setPosition(
		Common::shift(slider->getPosition(), 0, -_ttfSize * 1.2));
	_x_PixMessage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_x_PixMessage->setTextColor(Color4B::BLACK);
	addChild(_x_PixMessage);

	_y_PixMessage = Label::createWithTTF(dics->valueForKey("_y_PixMessage")->getCString(), __Chinese_TTF, 24);
	_y_PixMessage->setContentSize(Size(_x_PixMessage->getContentSize().width, _x_PixMessage->getContentSize().height));
	_y_PixMessage->setPosition(
		Common::shift(_x_PixMessage->getPosition(), 0, -_ttfSize * 1.2));
	_y_PixMessage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_y_PixMessage->setTextColor(Color4B::BLACK);
	addChild(_y_PixMessage);

	_real_x = Label::createWithTTF(dics->valueForKey("_real_x")->getCString(), __Chinese_TTF, 24);
	_real_x->setContentSize(Size(_x_PixMessage->getContentSize().width, _x_PixMessage->getContentSize().height));
	_real_x->setPosition(
		Common::shift(_x_PixMessage->getPosition(), _chromaticityDiagram->getContentSize().width*0.5, 0));
	_real_x->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_real_x->setTextColor(Color4B::BLACK);
	addChild(_real_x);

	_real_y = Label::createWithTTF(dics->valueForKey("_real_y")->getCString(), __Chinese_TTF, 24);
	_real_y->setContentSize(Size(_y_PixMessage->getContentSize().width, _x_PixMessage->getContentSize().height));
	_real_y->setPosition(_real_x->getPosition().x, _y_PixMessage->getPosition().y);
	_real_y->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_real_y->setTextColor(Color4B::BLACK);
	addChild(_real_y);

	_concentration = Label::createWithTTF(dics->valueForKey("_concentration")->getCString(), __Chinese_TTF, 24);
	_concentration->setPosition(
		Common::shift(_y_PixMessage->getPosition(),0 , -_ttfSize * 1.2));
	_concentration->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_concentration->setTextColor(Color4B::BLACK);
	addChild(_concentration);

	//value editbox
	_x_PixVal = EditBox::create(Size(_chromaticityDiagram->getContentSize().width*0.25, _x_PixMessage->getContentSize().height),"button/white.png");
	_x_PixVal->setPosition(
		Common::shift(_x_PixMessage->getPosition(), _x_PixMessage->getContentSize().width, 0));
	_x_PixVal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_x_PixVal->setFontColor(Color4B(Color3B::BLACK,127));
	_x_PixVal->setTouchEnabled(false);
	addChild(_x_PixVal);

	_y_PixVal = EditBox::create(_x_PixVal->getContentSize(), "button/white.png");
	_y_PixVal->setPosition(Vec2(_x_PixVal->getPosition().x ,_y_PixMessage->getPosition().y ));
	_y_PixVal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_y_PixVal->setFontColor(Color4B(Color3B::BLACK, 127));
	_y_PixVal->setTouchEnabled(false);
	addChild(_y_PixVal);

	_real_xVal = EditBox::create(_x_PixVal->getContentSize(), "button/white.png");
	_real_xVal->setPosition(
		Common::shift(_real_x->getPosition(), _real_x->getContentSize().width, 0));
	_real_xVal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_real_xVal->setFontColor(Color4B(Color3B::BLACK, 127));
	_real_xVal->setTouchEnabled(false);
	addChild(_real_xVal);

	_real_yVal = EditBox::create(_x_PixVal->getContentSize(), "button/white.png");
	_real_yVal->setPosition(
		Common::shift(_real_y->getPosition(), _real_y->getContentSize().width, 0));
	_real_yVal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_real_yVal->setFontColor(Color4B(Color3B::BLACK, 127));
	_real_yVal->setTouchEnabled(false);
	addChild(_real_yVal);

	_concentrationVal = EditBox::create(_x_PixVal->getContentSize(), "button/white.png");
	_concentrationVal->setPosition(
		Common::shift(_y_PixVal->getPosition(),0, -_ttfSize * 1.2));
	_concentrationVal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_concentrationVal->setFontColor(Color4B(Color3B::BLACK, 127));
	_concentrationVal->setTouchEnabled(false);
	addChild(_concentrationVal);
	
	//set color visualize
	_color = Label::createWithTTF(dics->valueForKey("_color")->getCString(), __Chinese_TTF, 24);
	_color->setContentSize(Size(_chromaticityDiagram->getPosition().x - __designEdgeGap, _ttfSize));
	_color->setPosition(
		__designEdgeGap / 2, Winsize.height - __designEdgeGap / 2);
	_color->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_color->setTextColor(Color4B::BLACK);
	addChild(_color);

	_colorwindow = Sprite::create();
	_colorwindow->setContentSize(Size(_color->getContentSize().width,
		_color->getContentSize().width));
	_colorwindow->setPosition(
		Common::shift(_color->getPosition(), 0, -_color->getContentSize().height));
	_colorwindow->setTextureRect(Rect(Vec2(0, 0), _colorwindow->getContentSize()));
	_colorwindow->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_colorwindow->setColor(Color3B::YELLOW);
	addChild(_colorwindow); 

	_colorVal = EditBox::create(Size(_colorwindow->getContentSize().width, _ttfSize), "button/white.png");
	_colorVal->setPosition(
		Common::shift(_colorwindow->getPosition(), 0, -_colorwindow->getContentSize().height*1.1));
	_colorVal->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_colorVal->setFontColor(Color4B(Color3B::BLACK, 127));
	_colorVal->setTouchEnabled(false); 
	addChild(_colorVal);

	_message1 = EditBox::create(Size(_chromaticityDiagram->getContentSize().width,_ttfSize), "button/pure.png");
	_message1->setPosition(Vec2(_chromaticityDiagram->getPosition().x, _ttfSize * 2));
	_message1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_message1->setFontColor(Color4B(Color3B::BLACK, 127));
	_message1->setTouchEnabled(false);
	addChild(_message1);

	_message2 = EditBox::create(Size(_chromaticityDiagram->getContentSize().width, _ttfSize), "button/pure.png");
	_message2->setPosition(Vec2(_chromaticityDiagram->getPosition().x, _ttfSize ));
	_message2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_message2->setFontColor(Color4B(Color3B::BLACK, 127));
	_message2->setTouchEnabled(false);
	addChild(_message2);

	unabled_UI();
	
}

void DisplayLayer::set1DAnalysisModel() {
	_OneDdraw = DrawNode::create();
	_OneDdraw->setLocalZOrder(2);
	for (int i = 0; i < __devided; i++) {
		_OneDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), -50, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Common::shift(_chromaticityDiagram->getPosition(), 0, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Color4F(Color3B::BLACK, 1));
		_OneDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), -5, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)-5),
			Common::shift(_chromaticityDiagram->getPosition(), 0, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Color4F(Color3B::BLACK, 1));
		_OneDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), -5, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)+5),
			Common::shift(_chromaticityDiagram->getPosition(), 0, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Color4F(Color3B::BLACK, 1));
	}
	_OneDdraw->setVisible(false);
	addChild(_OneDdraw);
}

void DisplayLayer::set2DAnalysisModel() {
	_TwoDdraw = DrawNode::create();
	_TwoDdraw->setLocalZOrder(2);
	for (int i = 0; i < __devided; i++) {
		_TwoDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), -25, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Common::shift(_chromaticityDiagram->getPosition(), 0, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Color4F(Color3B::BLACK, 1));
		_TwoDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), -5, i*_chromaticityDiagram->getContentSize().height / (__devided - 1) - 5),
			Common::shift(_chromaticityDiagram->getPosition(), 0, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Color4F(Color3B::BLACK, 1));
		_TwoDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), -5, i*_chromaticityDiagram->getContentSize().height / (__devided - 1) + 5),
			Common::shift(_chromaticityDiagram->getPosition(), 0, i*_chromaticityDiagram->getContentSize().height / (__devided - 1)),
			Color4F(Color3B::BLACK, 1));

		_TwoDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), i*_chromaticityDiagram->getContentSize().width / (__devided - 1),-25 ),
			Common::shift(_chromaticityDiagram->getPosition(), i*_chromaticityDiagram->getContentSize().width / (__devided - 1), 0),
			Color4F(Color3B::BLACK, 1));
		_TwoDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), i*_chromaticityDiagram->getContentSize().width / (__devided - 1) - 5 ,-5),
			Common::shift(_chromaticityDiagram->getPosition(), i*_chromaticityDiagram->getContentSize().width / (__devided - 1), 0),
			Color4F(Color3B::BLACK, 1));
		_TwoDdraw->drawLine(Common::shift(_chromaticityDiagram->getPosition(), i*_chromaticityDiagram->getContentSize().width / (__devided - 1) + 5, -5),
			Common::shift(_chromaticityDiagram->getPosition(), i*_chromaticityDiagram->getContentSize().width / (__devided - 1), 0),
			Color4F(Color3B::BLACK, 1));
	}
	_TwoDdraw->setVisible(false);
	addChild(_TwoDdraw);
}

void DisplayLayer::prepareForImages() {
	if (_isprepared == true)
		return;

	Texture2D* tex = _chromaticityDiagram->getTexture();
	RenderTexture* pRender = RenderTexture::create(_chromaticityDiagram->getContentSize().width, _chromaticityDiagram->getContentSize().height, Texture2D::PixelFormat::RGBA8888);

	Director::getInstance()->getRenderer()->render();

	//prepare for oned
	for (int i = 0; i <= __MaxYear; i++) {
		Image* imag = pRender->newImage();
		oned_imags.pushBack(imag);
		Texture2D* tex = new Texture2D;//texture一定要image先内存处理好在initwithimage,不然不会正常显示
		oned_texs.pushBack(tex);
	}

	//prepare for twod
	for (int i = 0; i <= __MaxYear; i++) {
		Image* imag = pRender->newImage();
		twod_imags.pushBack(imag);
		Texture2D* tex = new Texture2D;//texture一定要image先内存处理好在initwithimage,不然不会正常显示
		twod_texs.pushBack(tex);
	}

	_isprepared = true;
}

void DisplayLayer::startAnalysis(double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
	double k,
	int x_mm, int y_mm) {

	unabled_UI();

	max_x_mm = x_mm;
	max_y_mm = y_mm;

	prepareForImages();

	//while the origin year,oned
	Color4B c = getRGBA(Co);
	unsigned char* _data = oned_imags.at(0)->getData();
	int s = oned_imags.at(0)->getDataLen();
	for (int i = 0; i < s / 4; i++) {
		*((int *)_data) = *((int *)&c);
		_data += 4;
	}
	oned_texs.at(0)->initWithImage(oned_imags.at(0));

	//while the origin year,twod
	_data = twod_imags.at(0)->getData();
	s = twod_imags.at(0)->getDataLen();
	for (int i = 0; i < s / 4; i++) {
		*((int *)_data) = *((int *)&c);
		_data += 4;
	}
	twod_texs.at(0)->initWithImage(twod_imags.at(0));

	image_width = oned_imags.at(0)->getWidth();//522
	image_height = oned_imags.at(0)->getHeight();//468
	image_len = oned_imags.at(0)->getDataLen();//977184

	//calculate all the Error value in these input constant
	if (!newErrValueArr()) {
		LOG_DisplayLayer("nerwErrValueArr false");
		return;
	}		
	calculateAllValuableErr( m,  Do,  to,
		 H,  Hc,  U,  R,  To,  T,  a,  b,  N,
		 k);

	//while the other year from 1-100
	for (int t = 1; t <= __MaxYear; t++) {//every year
		Texture2D* one_tex = oned_texs.at(t);
		Image* one_im = oned_imags.at(t);

		Texture2D* two_tex = twod_texs.at(t);
		Image* two_im = twod_imags.at(t);

		double err1, err2, cl;
		for (int j = 0; j < image_width; j++) {//every x
			double x = xPixelTox(j);
			int i1 = x * 100;
			x = (double)i1 / 100;

			//set oned
			err1 = *getAddressFromErrarr(
				t, x);
			cl = Co + (Cs - Co)*(1 - err1);
			Color4B c = getRGBA(cl);
			setImage(c, one_tex, one_im, j);

			//set twod
			for (int k = 0; k < _chromaticityDiagram->getContentSize().height; k++) {//every y
				double y = xPixelTox(image_height-k);

				err2 = err1 == 0 ? 0: *getAddressFromErrarr(
					t, y);
				cl = Co + (Cs - Co)*(1 - err1*err2);
				Color4B c = getRGBA(cl);
				setImage(c, two_tex, two_im,j,k);
			}
		}
		one_tex->initWithImage(one_im);
		two_tex->initWithImage(two_im);

		LOG_DisplayLayer(__String::createWithFormat("the image of %d year has been finished", t)->getCString());
	}

	//free Error value Arr
	freeErrValueArr();
	
	setOneD_surface(getRGBA(Cs));
	setTwoD_surface(getRGBA(Cs));
	show_surface_cl();

	showYear(0);

	enabled_UI();
}


void DisplayLayer::showYear(int year) {
	if (__model == OneD) {
		_chromaticityDiagram->setTexture(oned_texs.at(year));
	}
	switch (__model)
	{
	case OneD:
		_chromaticityDiagram->setTexture(oned_texs.at(year));
		break;
	case TwoD:
		_chromaticityDiagram->setTexture(twod_texs.at(year));
		break;
	default:
		break;
	}

}

Color4B DisplayLayer::getRGBA(double cl) {//According to the Cl to get RGBA
	if (cl <= 0.25) {
		return Color4B(0,255, 255 * 4*cl, 255);
	}
	else if (cl <= 0.5) {
		return Color4B(0, 255 * (2 - 4 * cl), 255,  255);
	}
	else if (cl <= 0.75) {
		return Color4B(255 * 4 * (cl - 0.5), 0, 255, 255);
	}
	else {
		return Color4B(255, 0, 255* (4 - 4*cl), 255);
	}
}

double DisplayLayer::getCL(Color4B c) {//According to the RGBA to get cl

	double bitVal = 0.25 / 0xff;

	double ret;

	if (c.r == 0) {
		if (c.g == 0xff) {
			ret =  c.b*bitVal;
		}
		else {
			ret = 0.5 - c.g*bitVal;
		}
	}
	else {
		if (c.b == 0xff) {
			ret = 0.5 + c.r*bitVal;
		}
		else {
			ret = 1 - c.b*bitVal;
		}
	}
	return ret + 0.000001;
}

inline double DisplayLayer::xPixelTox(int px) {
	return px * max_x_mm / _chromaticityDiagram->getContentSize().width;
}

inline double DisplayLayer::yPixelToy(int py) {
	return py * max_y_mm / _chromaticityDiagram->getContentSize().height;
}

void DisplayLayer::slider_call_back(Ref* ref, Control::EventType controlEvents) {
	ControlSlider* slider = dynamic_cast<ControlSlider*>(ref);
	int year = (int)slider->getValue();
	__String* str = String::createWithFormat("%d", year);
	slide_num->setText(str->getCString());
	showYear(year);
}

void DisplayLayer::setImage(Color4B color, Texture2D* tx, Image* im, int px) {
	unsigned char * _data = im->getData();
	for (int i = 0; i < image_height; i++) {
		int offset = (image_width*i + px) * 4;
		*((int *)(_data + offset)) = *((int*)(&color));
	}
}

void DisplayLayer::setImage(Color4B color, Texture2D* tx, Image* im, int px, int py) {
	unsigned char * _data = im->getData();
	int offset = (image_width*py + px) * 4;
	int *address = (int *)(_data + offset);
	*((int *)(address)) = *((int*)(&color));
}

void DisplayLayer::unabled_UI() {
	slider->setEnabled(false);
	slide_num->setEnabled(false);
	yes->setEnabled(false);
}

void DisplayLayer::enabled_UI() {
	slider->setEnabled(true);
	slide_num->setEnabled(true);
	yes->setEnabled(true);
}

void DisplayLayer::setModel(int model) {
	switch (model)
	{
	case OneD:
		_OneDdraw->setVisible(true);
		_TwoDdraw->setVisible(false);
		break;
	default:
		_OneDdraw->setVisible(false);
		_TwoDdraw->setVisible(true);
		break;
	}
	__model = model;
	if (_isprepared) {
		showYear(slider->getValue());
		show_surface_cl();
	}
}

void DisplayLayer::show_surface_cl() {
	if (__model == OneD) {
		_OneDdraw->setVisible(true);
		_TwoDdraw->setVisible(false);
	}
	else if (__model == TwoD) {
		_OneDdraw->setVisible(false);
		_TwoDdraw->setVisible(true);
	}
}

void DisplayLayer::setOneD_surface(Color4B c) {
	if (_OneD_Surface_Cl)_OneD_Surface_Cl->removeFromParent();
	_OneD_Surface_Cl = DrawNode::create();
	_OneD_Surface_Cl->drawSolidRect(
		Common::shift(_chromaticityDiagram->getPosition(), -__designEdgeGap / 3, 0),
		Common::shift(_chromaticityDiagram->getPosition(), -__designContentGap, _chromaticityDiagram->getContentSize().height),
		Color4F(c)
	);
	addChild(_OneD_Surface_Cl);
	_OneD_Surface_Cl->setVisible(true);
}

void DisplayLayer::setTwoD_surface(Color4B c) {
	if (_TwoD_Surface_Cl)_TwoD_Surface_Cl->removeFromParent();
	_TwoD_Surface_Cl = DrawNode::create();
	_TwoD_Surface_Cl->drawSolidRect(
		Common::shift(_chromaticityDiagram->getPosition(), -__designEdgeGap / 3, 0),
		Common::shift(_chromaticityDiagram->getPosition(), -__designContentGap, _chromaticityDiagram->getContentSize().height),
		Color4F(c)
	);
	_TwoD_Surface_Cl->drawSolidRect(
		Common::shift(_chromaticityDiagram->getPosition(), 0, -__designEdgeGap / 3),
		Common::shift(_chromaticityDiagram->getPosition(), _chromaticityDiagram->getContentSize().width, -__designContentGap),
		Color4F(c)
	);
	addChild(_TwoD_Surface_Cl);
	_TwoD_Surface_Cl->setVisible(true);
}

bool DisplayLayer::newErrValueArr() {
	if (_ErrValueArr == nullptr)//I set the arr to 100 times bigger,in order to get pos=1.01,pos=1.43 like this
		_ErrValueArr = new double[MyMath::Max(max_x_mm, max_y_mm)*100*__MaxYear];

	return _ErrValueArr?true : false;
}
void DisplayLayer::freeErrValueArr() {
	if (_ErrValueArr) {
		delete[]_ErrValueArr;
		_ErrValueArr = nullptr;
	}
}
void DisplayLayer::calculateAllValuableErr(double m, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
	double k) {
	int length = MyMath::Max(max_x_mm, max_y_mm);
	for (int year = 1; year <= __MaxYear; year++) {//the arr start from the first year
		double * prev = nullptr;
		for (int pos = 0; pos < length*100; pos++) {
			double db = (double)pos / 100.0;
			double * ads = getAddressFromErrarr(year, db);
			prev = ads;

			double val = getError_CL(m, Do, to, H, Hc, U, R, To, T, a, b, N, k, (double)year*365*24*60*60, db);
			*ads = val;
		}
		LOG_DisplayLayer(__String::createWithFormat("Prepared the year of %d Error value has finished", year)->getCString());
	}
	LOG_DisplayLayer(__String::createWithFormat("Prepared all the Error value has finished")->getCString());
}

inline double* DisplayLayer::getAddressFromErrarr(int year, double pos) {
	int num = (pos+0.001) * 100.0;
	double* ads = (year - 1)*MyMath::Max(max_x_mm, max_y_mm)*100 + num + _ErrValueArr;
	return ads;
}

void DisplayLayer::addTouchListen() {
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [&](Touch* touch, Event*) {
		Point pt = touch->getLocation();
		if (Rect(
			Winsize.width*__designLRratio + _chromaticityDiagram->getPosition().x,
			_chromaticityDiagram->getPosition().y,
			_chromaticityDiagram->getContentSize().width,
			_chromaticityDiagram->getContentSize().height).containsPoint(pt))
		{
			return true;
		}
		return false;
	};
	ev->onTouchMoved = [&](Touch* touch, Event*) {
		Point pt = touch->getLocation();
		if (Rect(
			Winsize.width*__designLRratio+ _chromaticityDiagram->getPosition().x,
			_chromaticityDiagram->getPosition().y,
			_chromaticityDiagram->getContentSize().width,
			_chromaticityDiagram->getContentSize().height).containsPoint(pt))
		{
			if (_isprepared) {
				Vec2 v_to_diagram = Vec2(//the point based on button_left of diagram (0,0)
					pt.x - Winsize.width*__designLRratio - _chromaticityDiagram->getPosition().x,
					pt.y - _chromaticityDiagram->getPosition().y);
				set_dotLine(v_to_diagram);
				visualizeDataInDiagram(v_to_diagram);
			}
			
			return true;
		}
		return false;
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
}

void DisplayLayer::set_dotLine(Vec2 pos) {
	if (!_isprepared)
		return;
	else if (_dotLine != nullptr) {
		_dotLine->removeFromParent();
	}
	_dotLine = DotLine::create();
	_chromaticityDiagram->addChild(_dotLine);
	_dotLine->drawDotLine(2, 2, Vec2(pos.x, 0), Vec2(pos.x, _chromaticityDiagram->getContentSize().height), Color4F(Color3B::BLACK,127));
	_dotLine->drawDotLine(2, 2, Vec2(0, pos.y), Vec2(_chromaticityDiagram->getContentSize().width,pos.y), Color4F(Color3B::BLACK, 127));
	_dotLine->setLocalZOrder(3);
}

void DisplayLayer::visualizeDataInDiagram(Vec2 pixel) {
	int arr_y = image_height - pixel.y;
	int year = strToInt(slide_num->getText());

	Image * im = __model ? twod_imags.at(year) : oned_imags.at(year);
	int offset = (arr_y*image_width + pixel.x)*4;

	Color4B* data = (Color4B*)getColorFromImage(im, pixel.x, arr_y);
	Color4B invert = Color4B(data->a, data->b, data->g, data->r);

	int ix = pixel.x; int iy = pixel.y;

	//set pixel
	_x_PixVal->setText(__String::createWithFormat("%d", ix)->getCString());
	_y_PixVal->setText(__String::createWithFormat("%d", iy)->getCString());
	_real_xVal->setText(__String::createWithFormat("%lf", xPixelTox(ix))->getCString());
	_real_yVal->setText(__String::createWithFormat("%lf", yPixelToy(iy))->getCString());
	_colorVal->setText(__String::createWithFormat("%08x", *(&invert))->getCString());
	Color4B* c = (Color4B *)data;
	_colorwindow->setColor(Color3B(*c));
	
	_concentrationVal->setText(__String::createWithFormat("%.3lf", getCL(*data))->getCString());

	//CCLOG("memory address is %p", im->getData() + offset);
}

int* DisplayLayer::getColorFromImage(Image* im, int px, int py) {
	unsigned char * _data = im->getData();
	int offset = (image_width*py + px) * 4;
	return (int *)(_data + offset);
}

void DisplayLayer::LOG_DisplayLayer(const char* str) {
#ifdef MULTITHREAD
	#ifdef _WIN32
		mes = str;
	#else
		_message1->setText(_message2->getText());
		_message2->setText(str);
	#endif // _WIN32*/
#endif
#ifndef MULTITHREAD
		_message1->setText(_message2->getText());
		_message2->setText(str);
#endif // !MULTITHREAD

		
}

void DisplayLayer::thread_LOG() {
	while (1) {
		if (mes&&_message1&&_message2) {
			_message1->setText(_message2->getText());
			_message2->setText(mes);
			mes = nullptr;
		}
	}
}

void DisplayLayer::check_platform() {
#ifdef  _WIN32
	_platfrom = __WINDOWS__;
	LOG_DisplayLayer(__String::createWithFormat("Current enviroment:WIN32")->getCString());
#elif define _WIN64
	_platfrom = __WINDOWS__;
	LOG_DisplayLayer(__String::createWithFormat("Current enviroment:WIN64")->getCString());
#elif define __linux__
	_platfrom = __LINUX__;
	LOG_DisplayLayer(__String::createWithFormat("Current enviroment:LINUX")->getCString());
#else
	_platfrom = __ANDRIOD__;
	LOG_DisplayLayer(__String::createWithFormat("Current enviroment:ANDROID")->getCString());
#endif
}