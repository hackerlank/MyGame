#pragma once
#include "Global.h"
#include "cocos2d.h"
#include "UserProfileUI.h"
#include "NiuPlayer.h"
#include <vector>
#include <mutex>
#include <array>
using namespace std;
USING_NS_CC;

class PorkerManager;

//管理游戏中的玩家座位
class SiteManager
{
public:
	SiteManager(Node* parent,int currentPlayerID);
	virtual ~SiteManager();

	//玩家找个位置坐下
	bool joinSite(int playerID, string playerName, int diamond, int money);
	//离开座位
	bool leaveSite(int playerID);
	//设置倍数
	bool setMultiple(int playerID, int multiple);
	//显示倍数
	bool showMultiple(int playerID, bool isShow = true);
	//设置庄家
	bool showZhuangJia(int playerID);
	//显示牛
	bool showNiu(int playerID, int niuIndex);
	//隐藏所有牛
	void hideAllNiu();
	//显示准备
	bool showReady(int playerID, bool isShow = true);
	//当前入座玩家数量
	int currentPlayerCount() const;
	//显示聊天信息
	void showChatMessage(int playerID, string strMessage, float timeThreshold = 3.0f);

private:
	//玩家和头像位置信息
	struct PlayerAndProfilePos
	{
		Point playerPos;
		Point profilePos;
		Point niuPos;
		Point bubblePos;
		int profileType;		//0为水平，1为垂直
	};

private:
	array<NiuPlayer*,5> m_inRoomPlayer;
	array<PlayerAndProfilePos,5> m_playerProfileInfo;			//位置信息
	array<IUserProfileUIInGame*,5> m_pUserProfileVecs;			//头像UI，第0个是当前玩家头像
	array<int,5> m_playerInRoom;								//房间里的坑位，0表示没人坐，1表示有人坐
	array<int, 5> m_inRoomPlayerID;				//0为不存在
	array<Sprite*,5> m_playerNiu;
	map<int, string> m_niuIndex2JPGPath;

	int m_currentPlayerID;						//自己的ID

	Node* m_pParent;

	friend class PorkerManager;
	mutex m_lock;
};

