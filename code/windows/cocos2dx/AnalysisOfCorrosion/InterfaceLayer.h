#pragma once

#include "Common.h"
#include "DisplayLayer.h"

static char* mechanisms_name[__kindsOfMechanism] = { "linear"/*,"Fangmuir's","Langmuir's" */};
static char* mech_parameter[] = { "k","L'a","L'b","F'a","F'b" };

static char* input_constant[] = {
	"m",
	"Cs",
	"Co",
	"Do",
	"to",
	"H" ,
	"Hc",
	"U",
	"R",
	"To",
	"T",
	"N",
	"a",
	"b",
	"k",
	"x_mm",
	"y_mm"
};

class InterfaceLayer :public LayerColor
{
	friend class DisplayLayer;
public:
	CREATE_FUNC(InterfaceLayer);
	bool init();
	enum { _Linear, _Fangmuir, _Langmuir } mechanism;
	enum{Linear_k,F_a,F_b,L_a,L_b};
	enum input_sequence{m,Cs,Co,Do,to,H,Hc,U,R,To,T,N,a,b,k,x_mm,y_mm }sequence;

	void addItems();
	void ConnectWithDisplayLayer(DisplayLayer * l);
	void setDefaultValue();

protected:
	
	
private:
	__Dictionary* dics;
	DisplayLayer* dislay;

	RadioButtonGroup* combinedMechanism;
	Vector<RadioButton*> combiMechm;
	Vector<Label*>  machanismLabels;
	Vector<EditBox*> edits;

	RadioButtonGroup* models;
	RadioButton* OneDmodel;
	RadioButton* TwoDmodel;

	Vector<EditBox*> input_edits;

	Button* start;

	double _m ;
	double _Cs;
	double _Co;
	double _Do;
	double _to;
	double _H ;
	double _Hc;
	double _U ;
	double _R ;
	double _To;
	double _T ;
	double _a ;
	double _b ;
	double _N ;
	double _k ;
	double _x_mm ;
	double _y_mm ;

};
