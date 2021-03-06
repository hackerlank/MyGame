#include "UserProfileUI.h"
#include "PopupLayer.h"
#include "ShopLayer.h"
#include "MainScene.h"

UserProfileUI::UserProfileUI(Node* pParent)
{
	m_strPlayerName = "";
	m_nCoin = 0;
	m_lblDiamond = NULL;
	m_spHead = NULL;
	m_lblPlayerName = NULL;
	m_pParent = pParent;
	m_spFrame = NULL;
	m_spCoin = NULL;
	m_lblCoin = NULL;
}


UserProfileUI::~UserProfileUI()
{
}


HerizelUserProfileUI::HerizelUserProfileUI(Node* pParent) :IUserProfileUIInGame(pParent)
{

}

void HerizelUserProfileUI::showReady(bool isShow /* = true */)
{
	if (m_spReady)
	{
		m_spReady->setVisible(isShow);
	}
}


void HerizelUserProfileUI::showMultiple(bool isShow /* = true */)
{
	if (m_lblMultiple);
	{
		m_lblMultiple->setVisible(isShow);
	}
}

void HerizelUserProfileUI::showBanker(bool isShow /* = true */)
{
	if (m_spBankerFrame);
	{
		m_spBankerFrame->setVisible(isShow);
	}
}

bool HerizelUserProfileUI::setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin, const int multiple)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	if (!m_spFrame)
	{
		m_spFrame = Sprite::create("MainScene/userProfileFrame.png");
		if (!m_spFrame)
		{
			return false;
		}
		m_pParent->addChild(m_spFrame);
	}
	m_spFrame->setPosition(director->convertToUI(pos));
	if (!m_spBankerFrame)
	{
		m_spBankerFrame = Sprite::create("game/h_zhuang.png");
		if (!m_spBankerFrame)
		{
			return false;
		}
		m_spFrame->addChild(m_spBankerFrame);
		m_spBankerFrame->setPosition(Vec2(m_spFrame->getContentSize().width / 2 + 10, m_spFrame->getContentSize().height / 2 + 5));
	}
	if (!m_spHead)
	{
		m_spHead = Sprite::create(headFileName);
		if (!m_spHead)
		{
			return false;
		}

		m_spHead->setPosition(Vec2(55, 55));
		m_spFrame->addChild(m_spHead);
	}

	if (!m_lblPlayerName)
	{
		m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
		if (!m_lblPlayerName)
		{
			return false;
		}
		m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
		m_lblPlayerName->setPosition(Vec2(110, 90));
		m_spFrame->addChild(m_lblPlayerName);
	}
	m_lblPlayerName->setString(name);

	if (!m_spCoin)
	{
		m_spCoin = Sprite::create("MainScene/coin.png");
		if (!m_spCoin)
		{
			return false;
		}
		m_spCoin->setAnchorPoint(Vec2(0, 1));
		m_spCoin->setPosition(Vec2(105, 55));
		m_spFrame->addChild(m_spCoin);
	}

	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nCoin = diamond;
	if (!m_lblCoin)
	{
		m_lblCoin = LabelTTF::create(buf, "Arial", 25);
		if (!m_lblCoin)
		{
			return false;
		}
		m_lblCoin->setColor(Color3B(224, 179, 9));
		m_lblCoin->setAnchorPoint(Vec2(0, 1));
		m_lblCoin->setPosition(Vec2(165, 45));
		m_spFrame->addChild(m_lblCoin);
	}
	m_lblCoin->setString(buf);

	if (!m_spReady)
	{
		m_spReady = Sprite::create("game/ready.png");
		if (!m_spReady)
		{
			return false;
		}
		m_spReady->setPosition(Vec2(135, -45));
		m_spFrame->addChild(m_spReady);
	}

	vector<string> txts = { "", "x1", "x2", "x3", "x4", "x5" };
	if (!m_lblMultiple)
	{
		m_lblMultiple = LabelTTF::create(txts[multiple], "Arial", 30);
		if (!m_lblMultiple)
		{
			return false;
		}
		m_lblMultiple->setColor(Color3B::GREEN);
		m_lblMultiple->enableShadow(Size(3, -3), 1, 90);
		m_lblMultiple->setAnchorPoint(Vec2(0, 1));
		if (m_spFrame->getPosition().y <= 100)
		{
			m_lblMultiple->setPosition(Vec2(15, 150));
		}
		else
			m_lblMultiple->setPosition(Vec2(15, -10));
		m_spFrame->addChild(m_lblMultiple);
	}
	m_lblMultiple->setString(txts[multiple]);

	showMultiple(false);
	showBanker(false);
	showReady(false);
	return true;
}

bool IUserProfileUIInGame::setMultiple(int multiple)
{
	vector<string> txts = { "", "x1", "x2", "x3", "x4", "x5" };
	if (!m_lblMultiple)
	{
		m_lblMultiple = LabelTTF::create(txts[multiple], "Arial", 30);
		if (!m_lblMultiple)
		{
			return false;
		}
		m_lblMultiple->setColor(Color3B::GREEN);
		m_lblMultiple->enableShadow(Size(3, -3), 1, 90);
		m_lblMultiple->setAnchorPoint(Vec2(0, 1));
		if (m_spFrame->getPosition().y <= 100)
		{
			m_lblMultiple->setPosition(Vec2(15, 150));
		}
		else
			m_lblMultiple->setPosition(Vec2(15, -10));
		m_spFrame->addChild(m_lblMultiple);
	}
	m_lblMultiple->setString(txts[multiple]);
	showMultiple(false);
	showBanker(false);
	return true;
}


VerticalUserProfileUI::VerticalUserProfileUI(Node* pParent) :IUserProfileUIInGame(pParent)
{

}

void VerticalUserProfileUI::showMultiple(bool isShow /* = true */)
{
	if (m_lblMultiple);
	{
		m_lblMultiple->setVisible(isShow);
	}
}

void VerticalUserProfileUI::showReady(bool isShow /* = true */)
{
	if (m_spReady)
	{
		m_spReady->setVisible(isShow);
	}
}

void VerticalUserProfileUI::showBanker(bool isShow /* = true */)
{
	if (m_spBankerFrame)
	{
		m_spBankerFrame->setVisible(isShow);
	}
}

IUserProfileUIInGame* VerticalUserProfileUI::create(Node* pParent)
{
	IUserProfileUIInGame *ui = new (std::nothrow) VerticalUserProfileUI(pParent);
	if (ui)
	{
		//ui->retain();
		return ui;
	}
	CC_SAFE_DELETE(ui);
	return nullptr;
}

IUserProfileUIInGame* HerizelUserProfileUI::create(Node* pParent)
{
	IUserProfileUIInGame *ui = new (std::nothrow) HerizelUserProfileUI(pParent);
	if (ui)
	{
		//ui->retain();
		return ui;
	}
	CC_SAFE_DELETE(ui);
	return nullptr;
}

UserProfileUI* UserProfileUIInMainScene::create(Node* pParent)
{
	UserProfileUI *ui = new (std::nothrow) UserProfileUIInMainScene(pParent);
	if (ui)
	{
		//ui->retain();
		return ui;
	}
	CC_SAFE_DELETE(ui);
	return nullptr;
}


bool VerticalUserProfileUI::setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin, const int multiple)
{
	cocos2d::Size Size = Director::getInstance()->getVisibleSize();
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	if (!m_spFrame)
	{
		m_spFrame = Sprite::create("MainScene/userProfileFrameV.png");
		if (!m_spFrame)
		{
			return false;
		}
		m_pParent->addChild(m_spFrame);
	}
	m_spFrame->setPosition(director->convertToUI(pos));
	if (!m_spBankerFrame)
	{
		m_spBankerFrame = Sprite::create("game/v_zhuang.png");
		if (!m_spBankerFrame)
		{
			return false;
		}
		m_spFrame->addChild(m_spBankerFrame);
		m_spBankerFrame->setPosition(Vec2(m_spFrame->getContentSize().width / 2 + 10, m_spFrame->getContentSize().height / 2 + 5));
	}
	if (!m_spHead)
	{
		m_spHead = Sprite::create(headFileName);
		if (!m_spHead)
		{
			return false;
		}
		m_spHead->setPosition(Vec2(62, 120));
		m_spFrame->addChild(m_spHead);
	}
	if (!m_lblPlayerName)
	{
		m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
		if (!m_lblPlayerName)
		{
			return false;
		}
		m_lblPlayerName->setPosition(Vec2(m_spFrame->getContentSize().width / 2, 60));
		m_spFrame->addChild(m_lblPlayerName);
	}
	m_lblPlayerName->setString(name);
	if (!m_spCoin)
	{
		m_spCoin = Sprite::create("MainScene/coin.png");
		if (!m_spCoin)
		{
			return false;
		}
		m_spCoin->setAnchorPoint(Vec2(0, 1));
		m_spCoin->setPosition(Vec2(5, 45));
		m_spFrame->addChild(m_spCoin);
	}
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nCoin = diamond;
	if (!m_lblCoin)
	{
		m_lblCoin = LabelTTF::create(buf, "Arial", 20);
		if (!m_lblCoin)
		{
			return false;
		}
		m_lblCoin->setColor(Color3B(255, 252, 0));
		m_lblCoin->setAnchorPoint(Vec2(0, 1));
		m_lblCoin->setPosition(Vec2(55, 35));
		m_spFrame->addChild(m_lblCoin);
	}
	m_lblCoin->setString(buf);

	if (!m_spReady)
	{
		m_spReady = Sprite::create("game/ready.png");
		if (!m_spReady)
		{
			return false;
		}
		m_spReady->setAnchorPoint(Vec2(0, 1));
		if (m_spFrame->getPosition().x <= 100)
		{
			m_spReady->setPosition(Vec2(145, 110));
		}
		else
			m_spReady->setPosition(Vec2(-130, 110));
		
		m_spFrame->addChild(m_spReady);
	}

	vector<string> txts = { "", "x1", "x2", "x3", "x4", "x5" };
	if (!m_lblMultiple)
	{
		m_lblMultiple = LabelTTF::create(txts[multiple], "Arial", 30);
		if (!m_lblMultiple)
		{
			return false;
		}
		m_lblMultiple->setColor(Color3B::GREEN);
		//m_lblMultiple->enableShadow(Size(3, -3), 1, 90);
		m_lblMultiple->setAnchorPoint(Vec2(0, 1));
		if (m_spFrame->getPosition().x <= 100)
		{
			m_lblMultiple->setPosition(Vec2(145, 170));
		}
		else
			m_lblMultiple->setPosition(Vec2(-45, 170));
		m_spFrame->addChild(m_lblMultiple);
	}
	m_lblMultiple->setString(txts[multiple]);


	showMultiple(false);
	showBanker(false);
	showReady(false);

	return true;
}

UserProfileUIInMainScene::UserProfileUIInMainScene(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin) :
UserProfileUI(pParent)
{
	auto director = Director::getInstance();
	m_spRoundRect = Sprite::create("MainScene/roundRect.png");
	m_spRoundRect->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect->setPosition(director->convertToUI(Vec2(90, 65)));
	m_pParent->addChild(m_spRoundRect);
	m_spRoundRect2 = Sprite::create("MainScene/roundRect3.png");
	m_spRoundRect2->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect2->setPosition(director->convertToUI(Vec2(380, 65)));
	m_pParent->addChild(m_spRoundRect2);
	m_spHead = Sprite::create(headFileName);
	m_spHead->setAnchorPoint(Vec2(0,1));
	m_spHead->setPosition(director->convertToUI(pos));
	m_pParent->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 25);
	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
	m_lblPlayerName->setPosition(director->convertToUI(Vec2(130,27)));
	m_pParent->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(director->convertToUI(Vec2(125, 65)));
	m_pParent->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(director->convertToUI(Vec2(180, 75)));
	m_pParent->addChild(m_lblDiamond);
	m_btnAddDiamond = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
	m_btnAddDiamond->setScale9Enabled(true);
	m_btnAddDiamond->setAnchorPoint(Vec2(0, 1));
	m_btnAddDiamond->setPosition(director->convertToUI(Vec2(300,63)));
	m_pParent->addChild(m_btnAddDiamond);
	m_btnAddDiamond->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));

	m_spCoin = Sprite::create("MainScene/coin.png");
	m_spCoin->setAnchorPoint(Vec2(0, 1));
	m_spCoin->setPosition(director->convertToUI(Vec2(380, 65)));
	m_pParent->addChild(m_spCoin);
	sprintf(buf, "%d", coin);
	m_nCoin = coin;
	m_lblCoin = LabelTTF::create(buf, "Arial", 25);
	m_lblCoin->setColor(Color3B(224, 179, 9));
	m_lblCoin->setAnchorPoint(Vec2(0, 1));
	m_lblCoin->setPosition(director->convertToUI(Vec2(435, 75)));
	m_pParent->addChild(m_lblCoin);
	m_btnAddCoin = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
	m_btnAddCoin->setScale9Enabled(true);
	m_btnAddCoin->setAnchorPoint(Vec2(0, 1));
	m_btnAddCoin->setPosition(director->convertToUI(Vec2(540, 63)));
	m_pParent->addChild(m_btnAddCoin);
	m_btnAddCoin->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));
}

UserProfileUIInMainScene::UserProfileUIInMainScene(Node* pParent) :UserProfileUI(pParent)
{
	m_spRoundRect = NULL;
	m_btnAddDiamond = NULL;
	m_spRoundRect2 = NULL;
	m_btnAddCoin = NULL;
	m_spDianmond = NULL;
	m_lblCoin = NULL;
	m_lblDiamond = NULL;
	m_lblPlayerName = NULL;
}

bool UserProfileUIInMainScene::setProfile(Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	if (!m_spRoundRect)
	{
		m_spRoundRect = Sprite::create("MainScene/roundRect.png");
		if (!m_spRoundRect)
		{
			return false;
		}
		m_pParent->addChild(m_spRoundRect);
	}
	m_spRoundRect->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect->setPosition(director->convertToUI(Vec2(90, 65)));
	
	if (!m_spHead)
	{
		m_spHead = Sprite::create(headFileName);
		if (!m_spHead)
		{
			return false;
		}
		m_pParent->addChild(m_spHead);
	}
	m_spHead->setAnchorPoint(Vec2(0, 1));
	m_spHead->setPosition(director->convertToUI(pos));
	
	if (!m_lblPlayerName)
	{
		m_lblPlayerName = LabelTTF::create(name, "Arial", 25);
		if (!m_lblPlayerName)
		{
			return false;
		}
		m_pParent->addChild(m_lblPlayerName);
	}
	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
	m_lblPlayerName->setPosition(director->convertToUI(Vec2(130, 27)));
	m_lblPlayerName->setString(name);
	
	if (!m_spDianmond)
	{
		m_spDianmond = Sprite::create("MainScene/diamond.png");
		if (!m_spDianmond)
		{
			return false;
		}
		m_pParent->addChild(m_spDianmond);
	}
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(director->convertToUI(Vec2(125, 65)));
	
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	if (!m_lblDiamond)
	{
		m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
		if (!m_lblDiamond)
		{
			return false;
		}
		m_pParent->addChild(m_lblDiamond);
	}
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(director->convertToUI(Vec2(180, 75)));
	m_lblDiamond->setString(buf);
	
	if (!m_btnAddDiamond)
	{
		m_btnAddDiamond = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
		if (!m_btnAddDiamond)
		{
			return false;
		}
		m_pParent->addChild(m_btnAddDiamond);
	}
	m_btnAddDiamond->setScale9Enabled(true);
	m_btnAddDiamond->setAnchorPoint(Vec2(0, 1));
	m_btnAddDiamond->setPosition(director->convertToUI(Vec2(300, 63)));
	m_btnAddDiamond->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));

	if (!m_spCoin)
	{
		m_spCoin = Sprite::create("MainScene/coin.png");
		if (!m_spCoin)
		{
			return false;
		}
		m_pParent->addChild(m_spCoin);
	}
	m_spCoin->setAnchorPoint(Vec2(0, 1));
	m_spCoin->setPosition(director->convertToUI(Vec2(380, 65)));
	
	sprintf(buf, "%d", coin);
	m_nCoin = coin;
	if (!m_lblCoin)
	{
		m_lblCoin = LabelTTF::create(buf, "Arial", 25);
		if (!m_lblCoin)
		{
			return false;
		}
		m_pParent->addChild(m_lblCoin);
	}
	m_lblCoin->setColor(Color3B(224, 179, 9));
	m_lblCoin->setAnchorPoint(Vec2(0, 1));
	m_lblCoin->setPosition(director->convertToUI(Vec2(435, 75)));
	m_lblCoin->setString(buf);
	
	if (!m_btnAddCoin)
	{
		m_btnAddCoin = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
		if (!m_btnAddCoin)
		{
			return false;
		}
		m_pParent->addChild(m_btnAddCoin);
	}

	m_btnAddCoin->setScale9Enabled(true);
	m_btnAddCoin->setAnchorPoint(Vec2(0, 1));
	m_btnAddCoin->setPosition(director->convertToUI(Vec2(540, 63)));
	
	m_btnAddCoin->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));
	return true;
}

void UserProfileUIInMainScene::onAddBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	Button* pBtn = dynamic_cast<Button*>(pSender);
	MainScene* p = (MainScene*)m_pParent;
	if (type == Widget::TouchEventType::ENDED)
	{
		if (pBtn == m_btnAddCoin)
		{
			int i = p->getDiamond();
			Director::getInstance()->replaceScene(ShopLayer::createScene(p->getPlayerID(),p->getDiamond(),p->getMoney(),0));
		}
		else if (pBtn == m_btnAddDiamond)
		{
			log("add diamond");
			int i = p->getDiamond();
			Director::getInstance()->replaceScene(ShopLayer::createScene(p->getPlayerID(),p->getDiamond(),p->getMoney(),1));
		}
	}

}

UserProfileUIInMainScene::~UserProfileUIInMainScene()
{
	m_btnAddDiamond->removeFromParent();
	m_btnAddCoin->removeFromParent();
	m_lblDiamond->removeFromParent();
	m_lblCoin->removeFromParent();
	m_lblPlayerName->removeFromParent();
	m_spCoin->removeFromParent();
	m_spHead->removeFromParent();
	m_spRoundRect->removeFromParent();
	m_spDianmond->removeFromParent();
}