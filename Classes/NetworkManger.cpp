#include "NetworkManger.h"
#include "TCPClient.h"
#include "TCPRequest.h"

NetworkManger* NetworkManger::m_pInstance = NULL;

NetworkManger::NetworkManger()
{
}

NetworkManger* NetworkManger::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new NetworkManger;
	}
	return m_pInstance;
}

void NetworkManger::destroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
	}
}


NetworkManger::~NetworkManger()
{
}



bool NetworkManger::SendRequest_CreateUser(const S_CreatePlayerReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_strAccountLen), 2);
	pIndex += 2;
	for (int i = 0; i <= requestData.m_account.length(); ++i)
	{
//		*pIndex = requestData.m_account[i];
        memcpy(pIndex,requestData.m_account.c_str(),requestData.m_account.length());
        pIndex+=requestData.m_account.length();
        
    }
    memcpy(pIndex, ((char*)&requestData.m_strRoleNameLen), 2);
	pIndex += 2;
	for (int i = 0; i <= requestData.m_roleName.length(); ++i)
	{
//		(char)(*pIndex) = requestData.m_roleName[i];
//        pIndex++;
        memcpy(pIndex,requestData.m_roleName.c_str(),requestData.m_roleName.length());
        pIndex+=requestData.m_roleName.length();
	}
	memcpy(pIndex, ((char*)&requestData.m_sex), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_yanZhengMa), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_yanZhengTime), 4);
	pIndex += 4;
	
	//∑¢ÀÕ
	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete [] dataBuf;
	return ret;
}
bool NetworkManger::SendRequest_Login(const S_LoginReq& requestData)
{
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_strRoleNameLen), 2);
	pIndex += 2;
	for (int i = 0; i <= requestData.m_roleName.length(); ++i)
	{
		(char)(*pIndex++) = requestData.m_roleName[i];
	}
	memcpy(pIndex, ((char*)&requestData.m_checkTime), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_checkNum), 4);
	pIndex += 4;
	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}
bool NetworkManger::SendRequest_CreateRoom(const S_CreateRoomReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_wantBuy, 4);

	bool ret = false;
	
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;

	return ret;
}

bool NetworkManger::SendRequest_FaPai(const S_FaPaiReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_playerID), 8);

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_JoinRoom(const S_JoinRoomReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_roomID), 4);

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));
	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_QuitRoom(const S_QuitRoomReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_TanPai(const S_TanPaiReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_YaZhu(const S_YaZhuReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_beishu), 4);

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(void* requestData, int size)
{
	CTCPRequest *request = new CTCPRequest;
	request->retain();
	request->setRequestData((char*)requestData, size);
	bool ret = false;
	ret= m_tcpClient.sendTCPRequset(request);
	request->release();
	return ret;
}

void NetworkManger::shutDownNetwork()
{
	m_tcpClient.Destroy();
}

void NetworkManger::startNetwork()
{
	if (!m_tcpClient.isConnected())
	{
		m_tcpClient.Create(g_strServerIP.c_str(), g_nServerPort);
	}
}

bool  NetworkManger::CACKResponseQueue::isEmpty()
{
	return m_queue.empty();
}

S_ACKResponse NetworkManger::CACKResponseQueue::getFrontFromQueue()
{
	if (m_queue.empty())
	{
		S_ACKResponse S;
		return S;
	}
	return m_queue.front();
}

void NetworkManger::CACKResponseQueue::pushACKResponse(void* responseData, int size)
{
	S_ACKResponse s(responseData, size);
	m_queue.push_back(s);
}

void NetworkManger::CACKResponseQueue::popACKResponse()
{
	if (!m_queue.empty())
	{
		m_queue.pop_front();
	}
}

bool NetworkManger::ackQueueIsEmpty()
{
	return m_ackQueue.isEmpty();
}

void NetworkManger::pushACKQueue(void* data, int size)
{
	m_ackQueue.pushACKResponse(data, size);
}

void NetworkManger::popACKQueue()
{
	m_ackQueue.popACKResponse();
}

short NetworkManger::getQueueFrontACKCmd()
{
	short cmd = 0;
	S_ACKResponse s = m_ackQueue.getFrontFromQueue();
	memcpy(&cmd, s.m_buf + 2, 2);
	return ntohs(cmd);
}

void* NetworkManger::getQueueFrontACKBinaryData()
{
	return m_ackQueue.getFrontFromQueue().m_buf;
}