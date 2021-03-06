#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include <string>

USING_NS_CC;
using namespace ui;

class ShopLayer : public cocos2d::Layer
{
public:
	ShopLayer(int playerID, int diamond, int money, int number = 0);
	~ShopLayer();
	static Scene* createScene(int playerID,int diamond, int money, int number = 0);
	//static cocos2d::Scene* createScene(String str);
	virtual bool init();
	//CREATE_FUNC(ShopLayer);
	static ShopLayer* create(int playerID, int diamond, int money, int number = 0);
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
	//virtual void onEnter(int number);

private:
	bool initBackground();
	bool initButtons();			//商城图标、返回按钮初始化
	bool initMenuBar();			//左侧初始化导航条
	bool initTopMenuBar();		//顶部初始化导航条
	bool initShow();			//初始化显示框
	bool initDiamondLayer();	//初始化钻石层
	bool initCoinLayer();		//初始化金币层
	void tapBarMenuPressed(Ref *pSender);

	LayerMultiplex* layers;		//左侧层
	LayerMultiplex* topLayers;	//顶部层
	Menu* tabBarItems;			//左侧层菜单
	Menu* tabBarTopItems;		//顶部层菜单
	Layer* layerDiamond;		//钻石层
	Layer* layerCoin;			//金币层
	MenuItemSprite* buyDiamond;		//购买钻石精灵
	MenuItemSprite* buyCoin;		//购买金币精灵
	ccColor3B colBegan;				//钻石、金币精灵的颜色

	LabelTTF* m_lblDiamond;
	LabelTTF* m_lblCoin;

	LabelTTF* m_lblDiamond01;
	LabelTTF* m_lblDiamond02;
	LabelTTF* m_lblDiamond03;
	LabelTTF* m_lblDiamond04;
	LabelTTF* m_lblDiamond05;
	LabelTTF* m_lblDiamond06;

	LabelTTF* m_lblCoin01;
	LabelTTF* m_lblCoin02;
	LabelTTF* m_lblCoin03;
	LabelTTF* m_lblCoin04;
	LabelTTF* m_lblCoin05;
	LabelTTF* m_lblCoin06;

	Button* s_buyDiamond01Btn;
	Button* s_buyDiamond02Btn;
	Button* s_buyDiamond03Btn;
	Button* s_buyDiamond04Btn;
	Button* s_buyDiamond05Btn;
	Button* s_buyDiamond06Btn;

	LabelTTF* s_buyDiamond01Lab;
	LabelTTF* s_buyDiamond02Lab;
	LabelTTF* s_buyDiamond03Lab;
	LabelTTF* s_buyDiamond04Lab;
	LabelTTF* s_buyDiamond05Lab;
	LabelTTF* s_buyDiamond06Lab;

	Button* s_buyCoin01Btn;
	Button* s_buyCoin02Btn;
	Button* s_buyCoin03Btn;
	Button* s_buyCoin04Btn;
	Button* s_buyCoin05Btn;
	Button* s_buyCoin06Btn;

	int m_number;
	int m_playerID;
	int m_diamond;
	int m_money;
};

