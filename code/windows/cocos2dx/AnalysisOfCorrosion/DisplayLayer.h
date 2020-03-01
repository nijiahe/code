#pragma once

#include "Common.h"
#include "InterfaceLayer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件

#include "DotLine.h"

using namespace extension;


class DisplayLayer :public LayerColor
{
public:
	CREATE_FUNC(DisplayLayer);
	bool init();

	void startAnalysis(double m, double Cs, double Co, double Do, double to,
		double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
		double k,
		int x_mm, int y_mm);
	void showYear(int year);


	ControlSlider* slider;
	EditBox * slide_num;
	Label* word;
	Button* yes;
	__Dictionary* dics;

	void unabled_UI();
	void enabled_UI();

	void setModel(int model);
	void show_surface_cl();

	enum model {OneD,TwoD};
	enum platform {__WINDOWS__,__LINUX__,__ANDRIOD__};

protected:
	void addItems();
	void set1DAnalysisModel();
	void set2DAnalysisModel();
	void prepareForImages();
	
	Color4B getRGBA(double cl);//According to the Cl to get RGBA
	double getCL(Color4B);//According to the RGBA to get cl


	inline double xPixelTox(int px);
	inline double yPixelToy(int py);
	void setImage(Color4B color, Texture2D* tx,Image* im,int px);
	void setImage(Color4B color, Texture2D* tx, Image* im, int px,int py);
	int* getColorFromImage(Image* im,int px,int py);

	void setOneD_surface(Color4B c);
	void setTwoD_surface(Color4B c);

	void slider_call_back(Ref* ref, Control::EventType controlEvents);

	bool newErrValueArr();
	void freeErrValueArr();
	void calculateAllValuableErr(double m, double Do, double to,
		double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
		double k);
	//year is from 1 to _maxYear
	inline double* getAddressFromErrarr(int year, double pos);
	void addTouchListen();

	void set_dotLine(Vec2 pos);
	void visualizeDataInDiagram(Vec2 p);
	void LOG_DisplayLayer(const char * str);
	static void thread_LOG();
	void check_platform();

private:
	DrawNode* _OneDdraw;
	DrawNode* _TwoDdraw;
	DrawNode* _OneD_Surface_Cl = nullptr;
	DrawNode* _TwoD_Surface_Cl = nullptr;
	DotLine* _dotLine;
	Sprite* _chromaticityDiagram;

	Label* _x_PixMessage;	   EditBox* _x_PixVal;
	Label* _y_PixMessage;	   EditBox* _y_PixVal;
	Label* _real_x;			   EditBox* _real_xVal;
	Label* _real_y;			   EditBox* _real_yVal;
	Label* _color;			   EditBox* _colorVal;			Sprite* _colorwindow;
	Label* _concentration;	   EditBox* _concentrationVal;
	
	static EditBox* _message1; 
	static EditBox* _message2; 
	static const char* mes;

	Vector<Image*> oned_imags;
	Vector<Texture2D*> oned_texs;

	Vector<Image*> twod_imags;
	Vector<Texture2D*> twod_texs;

	double* _ErrValueArr;

	bool _isprepared = false;

	int max_x_mm = 0;
	int max_y_mm = 0;

	int image_width = 0;
	int image_height = 0;
	int image_len = 0;
	int __model = 0;
	int _platfrom = -1;
};
