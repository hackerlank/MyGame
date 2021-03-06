#include "SiteManager.h"
#include "ChatBubble.h"


SiteManager::SiteManager(Node* parent, int currentPlayerID)
{
	m_lock.lock();
	m_pParent = (Node*)parent;
	m_currentPlayerID = currentPlayerID;
	for (int i = 0; i < 5; ++i)
	{
		m_playerInRoom[i] = 0;
		m_inRoomPlayer[i] = nullptr;
		m_inRoomPlayerID[i] = 0;
		m_pUserProfileVecs[i] = nullptr;
		m_playerNiu[i] = nullptr;
	}
	cocos2d::Size Size = Director::getInstance()->getVisibleSize();
	m_playerProfileInfo[0].profilePos = Point(160, 550);
	m_playerProfileInfo[0].profileType = 0;
	m_playerProfileInfo[0].playerPos = Point(Size.width / 2, Size.height / 6 - 20);
	m_playerProfileInfo[0].niuPos = Point(Size.width / 2, Size.height / 6 + 60);
	m_playerProfileInfo[0].bubblePos = Point(25,150);
	m_playerProfileInfo[1].profilePos = Point(80, 330);
	m_playerProfileInfo[1].profileType = 1;
	m_playerProfileInfo[1].playerPos = Point(165, Size.height / 2 - 30);
	m_playerProfileInfo[1].niuPos = Point(240, Size.height / 2 - 90);
	m_playerProfileInfo[1].bubblePos = Point(25, 400);
	m_playerProfileInfo[2].profilePos = Point(400, 130);
	m_playerProfileInfo[2].profileType = 0;
	m_playerProfileInfo[2].playerPos = Point(Size.width*0.5 - pkWidth_small * 4 - 20, Size.height / 6 * 5 - 130);
	m_playerProfileInfo[2].niuPos = Point(Size.width*0.5 - 150, Size.height / 6 * 5 - 200);
	m_playerProfileInfo[2].bubblePos = Point(110, 520);
	m_playerProfileInfo[3].profilePos = Point(760, 130);
	m_playerProfileInfo[3].profileType = 0;
	m_playerProfileInfo[3].playerPos = Point(Size.width*0.5 + pkWidth_small * 3 - 100, Size.height / 6 * 5 - 130);
	m_playerProfileInfo[3].niuPos = Point(Size.width*0.5 + 150, Size.height / 6 * 5 - 200);
	m_playerProfileInfo[3].bubblePos = Point(900, 520);
	m_playerProfileInfo[4].profilePos = Point(1050, 330);
	m_playerProfileInfo[4].profileType = 1;
	m_playerProfileInfo[4].playerPos = Point(Size.width - pkWidth_small * 3 - 180, Size.height / 2 - 30);
	m_playerProfileInfo[4].niuPos = Point(Size.width - pkWidth_small * 3 - 85, Size.height / 2 - 90);
	m_playerProfileInfo[4].bubblePos = Point(950, 400);

	m_niuIndex2JPGPath[0] = "game/niu0.png";
	m_niuIndex2JPGPath[1] = "game/niu1.png";
	m_niuIndex2JPGPath[2] = "game/niu2.png";
	m_niuIndex2JPGPath[3] = "game/niu3.png";
	m_niuIndex2JPGPath[4] = "game/niu4.png";
	m_niuIndex2JPGPath[5] = "game/niu5.png";
	m_niuIndex2JPGPath[6] = "game/niu6.png";
	m_niuIndex2JPGPath[7] = "game/niu7.png";
	m_niuIndex2JPGPath[8] = "game/niu8.png";
	m_niuIndex2JPGPath[9] = "game/niu9.png";
	m_niuIndex2JPGPath[10] = "game/niuniu.png";
	m_niuIndex2JPGPath[11] = "game/zhadan.png";
	m_niuIndex2JPGPath[12] = "game/wuhuaniu.png";
	m_niuIndex2JPGPath[13] = "game/wuxiaoniu.png";

	m_lock.unlock();
}


SiteManager::~SiteManager()
{
	m_lock.lock();
	for (int i = 0; i < m_pUserProfileVecs.size(); ++i)
	{
		if (m_pUserProfileVecs[i] != nullptr)
		{
			delete m_pUserProfileVecs[i];
		}
	}
	for (int i = 0; i < m_inRoomPlayer.size(); ++i)
	{
		if (m_inRoomPlayer[i] != nullptr)
		{
			delete m_inRoomPlayer[i];
		}
	}
	m_lock.unlock();
}

void SiteManager::showChatMessage(int playerID, string strMessage, float timeThreshold /*= 3.0f*/)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			ChatBubble* t = ChatBubble::create(strMessage);
			m_pParent->addChild(t,10);
			t->setPosition(m_playerProfileInfo[i].bubblePos.x, m_playerProfileInfo[i].bubblePos.y);
			t->scheduleOnce(CC_SCHEDULE_SELECTOR(ChatBubble::onRemove), timeThreshold);
			break;
		}
	}
}

//返回当前入座人数
int SiteManager::currentPlayerCount() const
{
	int result = 0;
	for (int i = 0; i < m_playerInRoom.size(); ++i)
	{
		if (m_playerInRoom[i] == 1)
		{
			++result;
		}
	}
	return result;
}


//坐下座位
bool SiteManager::joinSite(int playerID, string playerName, int diamond, int money)
{
	for (int i = 0; i < m_playerInRoom.size(); ++i)
	{

			if (m_currentPlayerID == playerID)
			{
				if (m_playerInRoom[0] == 0)
				{
					m_lock.lock();
					m_pUserProfileVecs[i] = HerizelUserProfileUI::create(m_pParent);
					m_pUserProfileVecs[i]->setProfileProperty(m_playerProfileInfo[i].profilePos, "MainScene/timo.png", playerName, diamond, money, 0);
					m_inRoomPlayer[i] = new NiuPlayer;
					m_inRoomPlayer[i]->setPoint(m_playerProfileInfo[i].playerPos);
					m_inRoomPlayer[i]->setPlayerClass(PlayerType(i));
					m_playerInRoom[i] = 1;
					m_inRoomPlayerID[i] = playerID;
					m_lock.unlock();
					return true;
				}
			}
			else
			{
				if (m_playerInRoom[i] == 0 && i != 0)
				{
					m_lock.lock();
					switch (m_playerProfileInfo[i].profileType)
					{
					case 0:
					{
						m_pUserProfileVecs[i] = HerizelUserProfileUI::create(m_pParent);
						m_pUserProfileVecs[i]->setProfileProperty(m_playerProfileInfo[i].profilePos, "MainScene/timo.png", playerName, diamond, money, 0);
						m_inRoomPlayer[i] = new NiuPlayer;
						m_inRoomPlayer[i]->setPoint(m_playerProfileInfo[i].playerPos);
						m_inRoomPlayer[i]->setPlayerClass(PlayerType(i));
					}
					break;
					case 1:
					{
						m_pUserProfileVecs[i] = VerticalUserProfileUI::create(m_pParent);
						m_pUserProfileVecs[i]->setProfileProperty(m_playerProfileInfo[i].profilePos, "MainScene/timo.png", playerName, diamond, money, 0);
						m_inRoomPlayer[i] = new NiuPlayer;
						m_inRoomPlayer[i]->setPoint(m_playerProfileInfo[i].playerPos);
						m_inRoomPlayer[i]->setPlayerClass(PlayerType(i));
					}
					break;
					}
					m_playerInRoom[i] = 1;
					m_inRoomPlayerID[i] = playerID;
					m_lock.unlock();
					return true;
				}

			}

	}
	return false;
}

//离开座位
bool SiteManager::leaveSite(int playerID)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			m_lock.lock();
			delete m_pUserProfileVecs[i];
			m_pUserProfileVecs[i] = nullptr;
			m_inRoomPlayer[i]->emptyAllPokers();
			delete m_inRoomPlayer[i];
			m_inRoomPlayer[i] = nullptr;
			m_playerInRoom[i] = 0;
			m_inRoomPlayerID[i] = 0;
			m_lock.unlock();
			return true;
		}
	}
	return false;
}

//显示牛
bool SiteManager::showNiu(int playerID, int niuIndex)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			if (m_playerNiu[i])
			{
				m_playerNiu[i]->removeFromParent();
				m_playerNiu[i] = nullptr;
			}
			m_playerNiu[i] = Sprite::create(m_niuIndex2JPGPath[niuIndex]);
			if (!m_playerNiu[i])
			{
				return false;
			}
			m_pParent->addChild(m_playerNiu[i]);
			m_playerNiu[i]->setPosition(m_playerProfileInfo[i].niuPos);
			return true;
		}
	}
	return false;
}

//隐藏所有牛
void SiteManager::hideAllNiu()
{
	for (int i = 0; i < m_playerInRoom.size(); ++i)
	{
		if (m_playerInRoom[i] == 1)
		{
			if (m_playerNiu[i])
			{
				m_playerNiu[i]->removeFromParent();
				m_playerNiu[i] = nullptr;
			}
			
		}
	}
}

bool SiteManager::showZhuangJia(int playerID)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_pUserProfileVecs[i])
		{
			if (m_inRoomPlayerID[i] == playerID)
			{
				m_lock.lock();
				m_pUserProfileVecs[i]->showBanker(true);
				m_lock.unlock();
			}
			else
			{
				m_pUserProfileVecs[i]->showBanker(false);
			}
		}
	}
	return true;
}

bool SiteManager::setMultiple(int playerID, int multiple)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			m_lock.lock();
			m_pUserProfileVecs[i]->setMultiple(multiple);
			m_lock.unlock();
			return true;
		}
	}
	return false;
}

bool SiteManager::showReady(int playerID, bool isShow /* = true */)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			m_lock.lock();
			m_pUserProfileVecs[i]->showReady(isShow);
			m_lock.unlock();
			return true;
		}
	}
	return false;
}

bool SiteManager::showMultiple(int playerID, bool isShow /*= true*/)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			m_lock.lock();
			m_pUserProfileVecs[i]->showMultiple(isShow);
			m_lock.unlock();
			return true;
		}
	}
	return false;
}