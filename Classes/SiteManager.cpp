#include "SiteManager.h"


SiteManager::SiteManager(Node* parent, unsigned long long currentPlayerID) 
{
	m_lock.lock();
	m_pParent = parent;
	m_currentPlayerID = currentPlayerID;
	for (int i = 0; i < 5; ++i)
	{
		m_playerInRoom[i] = 0;
		m_inRoomPlayer[i] = nullptr;
		m_inRoomPlayerID[i] = 0;
		m_pUserProfileVecs[i] = nullptr;
	}
	cocos2d::Size Size = Director::getInstance()->getVisibleSize();
	m_playerProfileInfo[0].profilePos = Point(160, 550);
	m_playerProfileInfo[0].profileType = 0;
	m_playerProfileInfo[0].playerPos = Point(Size.width / 2, Size.height / 6 - 20);
	m_playerProfileInfo[1].profilePos = Point(80, 330);
	m_playerProfileInfo[1].profileType = 1;
	m_playerProfileInfo[1].playerPos = Point(165, Size.height / 2 - 30);
	m_playerProfileInfo[2].profilePos = Point(400, 130);
	m_playerProfileInfo[2].profileType = 0;
	m_playerProfileInfo[2].playerPos = Point(Size.width*0.5 - pkWidth_small * 4 - 20, Size.height / 6 * 5 - 130);
	m_playerProfileInfo[3].profilePos = Point(760, 130);
	m_playerProfileInfo[3].profileType = 0;
	m_playerProfileInfo[3].playerPos = Point(Size.width*0.5 + pkWidth_small * 3 - 100, Size.height / 6 * 5 - 130);
	m_playerProfileInfo[4].profilePos = Point(1050, 330);
	m_playerProfileInfo[4].profileType = 1;
	m_playerProfileInfo[4].playerPos = Point(Size.width - pkWidth_small * 3 - 180, Size.height / 2 - 30);
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

//������λ
bool SiteManager::joinSite(unsigned long long playerID, string playerName, int diamond, int money)
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

//�뿪��λ
bool SiteManager::leaveSite(unsigned long long playerID)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_inRoomPlayerID[i] == playerID)
		{
			m_lock.lock();
			delete m_pUserProfileVecs[i];
			m_pUserProfileVecs[i] = nullptr;
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

bool SiteManager::showZhuangJia(unsigned long long playerID)
{
	for (int i = 0; i < m_inRoomPlayerID.size(); ++i)
	{
		if (m_pUserProfileVecs[i])
		{
			if (m_inRoomPlayerID[i] == playerID)
			{
				m_lock.lock();
				m_pUserProfileVecs[i]->showBanker();
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

bool SiteManager::setMultiple(unsigned long long playerID, int multiple)
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

bool SiteManager::showReady(unsigned long long playerID, bool isShow /* = true */)
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
}

bool SiteManager::showMultiple(unsigned long long playerID,bool isShow /*= true*/)
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