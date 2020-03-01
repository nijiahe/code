#ifndef __Loading_Layer_H__
#define __Loading_Layer_H__

#include "Common.h"

class Loading_Layer:public Layer
{
public:
	CREATE_FUNC(Loading_Layer);
	bool init();
	void loading_source();
	void loading_label_monitor(float t);
	void process_label_monitor(float t);
	void loadImageCallBack(Texture2D* pic);
	void replacescene_Start_Layer();

	Label * _loading_label;
	Label * _process_label;
	ProgressTimer * _process_timer;
	int _total_file_num;
};

static char * picfile[] =
{
	"UI/AB_normal.png",
	"UI/AB_select.png",
	"UI/backA.png",
	"UI/backB.png",
	"UI/backKeyImage.png",
	"UI/backKeyLeft.png",
	"UI/backKeyRight.png",
	"UI/controlUI.png",
	"UI/left.png",
	"UI/music_off.png",
	"UI/music_on.png",
	"UI/M_n.png",
	"UI/M_s.png",
	"UI/right.png",
	"UI/sliderProgress.png",
	"UI/sliderTrack.png",
	"UI/sound_effect_off.png",
	"UI/sound_effect_on.png",
	"UI/switchBg.png",

	"Player_and_Monster/allow_walkLeft.png",
	"Player_and_Monster/allow_walkRight.png",
	"Player_and_Monster/arrowActionL.png",
	"Player_and_Monster/arrowActionR.png",
	"Player_and_Monster/arrow_die.png",
	"Player_and_Monster/boss.png",
	"Player_and_Monster/bossBullet.png",
	"Player_and_Monster/fireActionL.png",
	"Player_and_Monster/fireActionR.png",
	"Player_and_Monster/fireBall.png",
	"Player_and_Monster/fireLeft.png",
	"Player_and_Monster/fireRight.png",
	"Player_and_Monster/fire_die.png",
	"Player_and_Monster/flower0.png",
	"Player_and_Monster/flyFishLeft.png",
	"Player_and_Monster/flyFishRight.png",
	"Player_and_Monster/Mushroom0.png",
	"Player_and_Monster/normal_die.png",
	"Player_and_Monster/smallWalkLeft.png",
	"Player_and_Monster/smallWalkRight.png",
	"Player_and_Monster/small_die.png",
	"Player_and_Monster/tortoise0.png",
	"Player_and_Monster/walkLeft.png",
	"Player_and_Monster/WalkLeft_fire.png",
	"Player_and_Monster/walkRight.png",
	"Player_and_Monster/WalkRight_fire.png",

	"Menu/about_normal.png",
	"Menu/about_select.png",
	"Menu/newgameA.png",
	"Menu/newgameB.png",
	"Menu/nextlevel_normal.png",
	"Menu/nextlevel_select.png",
	"Menu/quitgame_normal.png",
	"Menu/quitgame_select.png",
	"Menu/restart_n.png",
	"Menu/restart_s.png",
	"Menu/resume_n.png",
	"Menu/resume_s.png",
	"Menu/retry_normal.png",
	"Menu/retry_select.png",
	"Menu/select_n.png",
	"Menu/select_s.png",
	"Menu/Setting_n.png",
	"Menu/setting_s.png",
	"Menu/set_n.png",
	"Menu/set_s.png",
	"Menu/startgame_normal.png",
	"Menu/startgame_select.png",


	"BackGround/background.png",
	"BackGround/backToMenu.png",
	"BackGround/bg.png",
	"BackGround/gameover.png",
	"BackGround/PassFailure.png",
	"BackGround/PassSuccess.png",
	"BackGround/Set_Menu.png",
	"BackGround/Set_Music.png",

	"arrow.png",
	"arrowBroken.png",
	"arrowBullet.png",
	"axe.png",
	"battery.png",
	"batteryBoom1.png",
	"batteryBoom2.png",
	"batteryBoom3.png",
	"batteryBullet.png",
	"blinkcoin.png",
	"brokencoin.png",
	"bulletBorder.png",
	"cloud.png",
	"coinani.png",
	"darkCloud.png",
	"flag.png",
	"ladder.png",
	"leftright.png",
	"lighting.png",
	"princess.png",
	"rewardMushroomSet.png",
	"shanshuodecoin.png",
	"singleblock.png",
	"superMarioMap.png",
	"Tools.png"
};

static char * music_file[] =
{
	"Sounds/AddLife.ogg",
	"Sounds/BossDiaoLuoQiaoXia.ogg",
	"Sounds/BossDie.ogg",
	"Sounds/BossHuoQiu.ogg",
	"Sounds/CaiSiGuaiWu.ogg",
	"Sounds/DiaoRuXianJingSi.ogg",
	"Sounds/DingChuMoGuHuoHua.ogg",
	"Sounds/DingPoZhuan.ogg",
	"Sounds/DingYingZhuanKuai.ogg",
	"Sounds/EatCoin.ogg",
	"Sounds/EatCoin.wma",
	"Sounds/EatMushroomOrFlower.ogg",
	"Sounds/GameOver.ogg",
	"Sounds/HuoQiuDaDaoGuaiWu.ogg",
	"Sounds/Jump.ogg",
	"Sounds/OnLand.ogg",
	"Sounds/OnLand.wma",
	"Sounds/QiZiLuoXia.ogg",
	"Sounds/RengHuoQiu.ogg",
	"Sounds/SuoXiao.ogg",
	"Sounds/YuDaoGuaiWuSi.ogg"
};

#endif