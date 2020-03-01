#include "InterfaceLayer.h"
#include "CommonAlgorithm.h"

int _ttfSize = 0;

bool InterfaceLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(240,240,240,240)))
	{
		return false;
	}
	dics = __Dictionary::createWithContentsOfFile(__Chinese_XML);

	addItems();
	

	return true;
}

void InterfaceLayer::addItems() {
	//mechanisms linear,...
	combinedMechanism = RadioButtonGroup::create();
	addChild(combinedMechanism);
	for (int i = 0; i < __kindsOfMechanism; i++) {
		RadioButton* button = RadioButton::create("button/radio-unchecked.png", "button/radio-checked.png");
		_ttfSize = button->getContentSize().height;
		button->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		combinedMechanism->addRadioButton(button);
		addChild(button);
		combiMechm.pushBack(button);
		button->setPosition(Vec2(__designEdgeGap,Winsize.height-(i+0.5)*(_ttfSize +__designContentGap)));
		Label* label = Label::createWithTTF(mechanisms_name[i], __Chinese_TTF, _ttfSize);
		label->setTextColor(Color4B::BLACK);
		addChild(label);
		label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		label->setPosition(button->getPosition().x + button->getContentSize().width + __designContentGap, button->getPosition().y);
		machanismLabels.pushBack(label);
	}
	
//models,oneD or TwoD
	//oneD model
	models = RadioButtonGroup::create();
	addChild(models);
	OneDmodel = RadioButton::create("button/radio-unchecked.png", "button/radio-checked.png");
	OneDmodel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	models->addRadioButton(OneDmodel);
	addChild(OneDmodel);
	OneDmodel->setPosition(
		Common::shift(combiMechm.at(0)->getPosition(), 0, -1.5*(_ttfSize + __designContentGap))
	);
	Label* label = Label::createWithTTF(dics->valueForKey("oneD model")->getCString(), __Chinese_TTF, _ttfSize);
	label->setTextColor(Color4B::BLACK);
	addChild(label);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(OneDmodel->getPosition().x + OneDmodel->getContentSize().width + __designContentGap, OneDmodel->getPosition().y);

	//twoD model
	TwoDmodel = RadioButton::create("button/radio-unchecked.png", "button/radio-checked.png");
	TwoDmodel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	models->addRadioButton(TwoDmodel);
	addChild(TwoDmodel);
	TwoDmodel->setPosition(
		Common::shift(OneDmodel->getPosition(), 0, -1.5*(_ttfSize + __designContentGap))
	);
	label = Label::createWithTTF(dics->valueForKey("twoD model")->getCString(), __Chinese_TTF, _ttfSize);
	label->setTextColor(Color4B::BLACK);
	addChild(label);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(TwoDmodel->getPosition().x + TwoDmodel->getContentSize().width + __designContentGap, TwoDmodel->getPosition().y);

	//one model button callback
	OneDmodel->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (!dynamic_cast<RadioButton*>(sender)->isSelected())
				dislay->setModel(DisplayLayer::model::OneD);
		}
	});
	//two model button callback
	TwoDmodel->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (!dynamic_cast<RadioButton*>(sender)->isSelected())
				dislay->setModel(DisplayLayer::model::TwoD);
		}
	});


	//input
	for (int i = 0; i < 5; i++) {
		EditBox* edit = EditBox::create(Size(50, _ttfSize),"button/checkbox-unchecked.png");
		edits.pushBack(edit);
		addChild(edit);
		edit->setFontName(__Chinese_TTF);
		edit->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		edit->setMaxLength(4);
		edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
		edit->setPlaceHolder(mech_parameter[i]);
		edit->setPlaceholderFontColor(Color3B(160,160,160));
		edit->setFontColor(Color3B::BLACK);
	}

	/*edits.at(Linear_k)->setPosition(Vec2(210, combiMechm.at(_Linear)->getPosition().y));
	edits.at(L_a)->setPosition(Vec2(210, combiMechm.at(_Fangmuir)->getPosition().y));
	edits.at(L_b)->setPosition(Vec2(270, combiMechm.at(_Fangmuir)->getPosition().y));
	edits.at(F_a)->setPosition(Vec2(210, combiMechm.at(_Langmuir)->getPosition().y));
	edits.at(F_b)->setPosition(Vec2(270, combiMechm.at(_Langmuir)->getPosition().y));*/

	for (int i = 0; i < sizeof(input_constant) / sizeof(char *) ; i++) {
		EditBox* edit = EditBox::create(Size(200, _ttfSize), "button/checkbox-unchecked.png");
		input_edits.pushBack(edit);
		addChild(edit);
		edit->setFontName(__Chinese_TTF);
		edit->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		edit->setMaxLength(10);
		edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
		edit->setPlaceHolder(dics->valueForKey(input_constant[i])->getCString());
		edit->setPlaceholderFontColor(Color3B(160, 160, 160));
		edit->setFontColor(Color3B::BLACK);
		edit->setPosition(Vec2(110, (i + 0.5)*(_ttfSize + __designContentGap)));

		Label* l = Label::createWithTTF(input_constant[i], __Chinese_TTF, _ttfSize);
		addChild(l);
		l->setColor(Color3B::BLACK);
		l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		l->setPosition(Vec2(__designEdgeGap, (i + 0.5)*(_ttfSize + __designContentGap)-2));
	}

	//start button
	start = Button::create("button/button_background_normal.png","button/button_background_pressed.png","button/button_background_normal.png");
	start->setTitleText(dics->valueForKey("analysis")->getCString());
	start->setTitleFontSize(_ttfSize);
	start->setTitleColor(Color3B::BLACK);
	addChild(start);
	start->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	Common::setConstentSize_comparedWithAnother(input_edits.at(0), start, 0.5f, 1.2f);
	start->setPosition(Common::shift(input_edits.back()->getPosition(), input_edits.back()->getContentSize().width, __designContentGap + _ttfSize));
	start->ignoreContentAdaptWithSize(false);

	setDefaultValue();

	//button_callback
	start->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

#define operation(x,y) (x==y?1:(y=x,is_change = true))

			double db_temp; int in_temp; bool is_change = false;
			db_temp = strToDouble(input_edits.at (input_sequence::m)->getText()); operation(db_temp, _m);
			db_temp = strToDouble(input_edits.at(input_sequence::Cs)->getText()); operation(db_temp, _Cs);
			db_temp = strToDouble(input_edits.at(input_sequence::Co)->getText()); operation(db_temp, _Co);
			db_temp = strToDouble(input_edits.at(input_sequence::Do)->getText()); operation(db_temp, _Do);
			db_temp = strToDouble(input_edits.at(input_sequence::to)->getText()); operation(db_temp, _to);
			db_temp = strToDouble(input_edits.at(input_sequence::H)->getText()); operation(db_temp, _H);
			db_temp = strToDouble(input_edits.at(input_sequence::Hc)->getText()); operation(db_temp,_Hc);
			db_temp = strToDouble(input_edits.at(input_sequence::U)->getText()); operation(db_temp, _U);
			db_temp = strToDouble(input_edits.at(input_sequence::R)->getText()); operation(db_temp, _R);
			db_temp = strToDouble(input_edits.at(input_sequence::To)->getText()); operation(db_temp,_To);
			db_temp = strToDouble(input_edits.at(input_sequence::T)->getText()); operation(db_temp, _T);
			db_temp = strToDouble(input_edits.at(input_sequence::a)->getText()); operation(db_temp, _a);
			db_temp = strToDouble(input_edits.at(input_sequence::b)->getText()); operation(db_temp, _b);
			db_temp = strToDouble(input_edits.at(input_sequence::N)->getText()); operation(db_temp, _N);
			db_temp = strToDouble(input_edits.at(input_sequence::k)->getText()); operation(db_temp, _k);
			in_temp = strToDouble(input_edits.at(input_sequence::x_mm)->getText());  operation(in_temp, _x_mm);
			in_temp = strToDouble(input_edits.at(input_sequence::y_mm)->getText());  operation(in_temp, _y_mm);
			
#undef operation(x,y)

			if (_m&&_Cs&&_Co&&_Do&&_to&&_H&&_Hc&&_U&&_R&&_To&&_T&&_a&&_b&&_N&&_k&&_b&&_x_mm&&_y_mm&&is_change) {
				dislay->startAnalysis(_m, _Cs, _Co, _Do, _to*365*24*60*60, _H, _Hc, _U, _R, _To, _T, _a, _b, _N, _k, _x_mm, _y_mm);
			}
		}
	});
}

void InterfaceLayer::ConnectWithDisplayLayer(DisplayLayer * l) {
	dislay = l;
}

void InterfaceLayer::setDefaultValue() {
	input_edits.at(m)->setText("0.5");
	input_edits.at(k)->setText("0.1");
	input_edits.at(Do)->setText("5");
	input_edits.at(H)->setText("0.5");
	input_edits.at(Hc)->setText("0.75");
	input_edits.at(U)->setText("41.8");
	input_edits.at(R)->setText("8.314");
	input_edits.at(a)->setText("1.05");
	input_edits.at(b)->setText("0.36");
	input_edits.at(x_mm)->setText("40");
	input_edits.at(y_mm)->setText("40");
	input_edits.at(Cs)->setText("0.9");
	input_edits.at(Co)->setText("0.1");
	input_edits.at(to)->setText("5");
	input_edits.at(T)->setText("283.15");
	input_edits.at(To)->setText("293.15");
}